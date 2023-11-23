/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:50:22 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:32:44 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

// Note: It is also to taken into consideration that an exit code
// with a value greater than 255 returns an exit code modulo 256.
// For Example: If we execute a statement exit(9999)
// then it will execute exit(15) as 9999%256 = 15.

int	check_exit_code(t_cmd *cmd, long exit_code)
{
	(void)cmd;
	if (exit_code > 255)
		exit_code = exit_code % 256;
	if (exit_code < 0)
		exit_code = exit_code % 256;
	return (exit_code);
}

int	count_sign(char *str)
{
	int	i;

	i = 1;
	if ((str[0] && (str[0] == '+' || str[0] == '-'))
		&& (str[1] && (str[1] == '+' || str[1] == '-')))
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	is_arg_numeric(t_cmd *cmd)
{
	int	i;

	i = 0;
	if ((*cmd->name[1]) == '\0')
		error_builtins(cmd, "numeric argument required", 2);
	if (count_sign(cmd->name[1]) == 0)
		return (error_builtins(cmd, "numeric argument required", 2), 0);
	while (cmd->name[1][i])
	{
		while (cmd->name[1][i] && (cmd->name[1][i] >= '0'
			&& cmd->name[1][i] <= '9'))
		{
			i++;
		}
		if (cmd->name[1][i] && (cmd->name[1][i] != '-'
			&& cmd->name[1][i] != '+'))
		{
			error_builtins(cmd, "numeric argument required", 2);
			return (0);
		}
		if (cmd->name[1][i])
			i++;
	}
	return (1);
}

int	check_arg(t_struct_data *s, t_cmd *cmd, long *exit_code)
{
	int	nbr_arg;

	nbr_arg = builtin_arg_nbr(cmd);
	if (nbr_arg > 1)
	{
		if (is_arg_numeric(cmd) == 0)
			free_and_exit(s, cmd, 2);
		if (ft_atol(cmd->name[1], exit_code) == 0)
		{
			error_builtins(cmd, "numeric argument required", 2);
			free_and_exit(s, cmd, 2);
		}
		if (nbr_arg > 2)
		{
			ft_putstr_fd("exit\n", 2);
			g_exit = 127;
			return (0);
		}
	}
	return (1);
}

void	builtin_exit(t_cmd *cmd, t_struct_data *s)
{
	long	exit_code;

	exit_code = 0;
	if (check_arg(s, cmd, &exit_code) == 0)
		return ;
	g_exit = check_exit_code(cmd, exit_code);
	free_exec(cmd);
	free_parsing(s);
	if (cmd->nbr != 1)
	{
		check_close(&cmd->fd.pipe[0]);
		check_close(&cmd->fd.pipe[1]);
	}
	check_close(&cmd->fd.write);
	if (cmd->heredoc == 0)
		check_close(&cmd->fd.read);
	else
		check_close(&cmd->fd.tmp);
	if (cmd->nbr == 1)
		ft_putstr_fd("exit\n", 1);
	exit(g_exit);
}
