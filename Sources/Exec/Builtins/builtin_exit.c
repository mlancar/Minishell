/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:50:22 by malancar          #+#    #+#             */
/*   Updated: 2023/11/13 19:32:37 by malancar         ###   ########.fr       */
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
	//probleme :
	if (exit_code < 0)
		exit_code = exit_code % 256;
	return (exit_code);
}

void	free_exec_and_parsing(t_lst_cmd *argv, t_cmd *cmd)
{
	(void)argv;
	free(cmd->argv);
	free(cmd->env);
	free(cmd->path);
	free(cmd->pid);
}

void	error_numeric_arg(t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minihsell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_exit = 2;
}

int	is_arg_numeric(t_cmd *cmd)
{
	int	i;

	i = 0;
	if ((*cmd->argv[1]) == '\0')
		error_numeric_arg(cmd);
	while (cmd->argv[1][i])
	{
		while (cmd->argv[1][i] && (cmd->argv[1][i] >= '0'
			&& cmd->argv[1][i] <= '9'))
		{
			i++;
		}
		if (cmd->argv[1][i] && (cmd->argv[1][i] != '-'
			&& cmd->argv[1][i] != '+'))
		{
			error_numeric_arg(cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_arg(t_cmd *cmd, long *exit_code)
{
	int	nbr_arg;
	
	nbr_arg = builtin_arg_nbr(cmd);
	if (nbr_arg > 1)
	{
		if (is_arg_numeric(cmd) == 0)
			free_and_exit(cmd, 2);
		if (ft_atol(cmd->argv[1], exit_code) == 0)
		{
			error_numeric_arg(cmd);
			free_and_exit(cmd, 2);
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

int	builtin_exit(t_lst_cmd *argv, t_cmd *cmd)
{
	long	exit_code;
	
	exit_code = 0;
	if (check_arg(cmd, &exit_code) == 0)
		return (0);
	g_exit = check_exit_code(cmd, exit_code);
	free_exec_and_parsing(argv, cmd);
	if (cmd->nbr != 1)
	{
		check_close(cmd, cmd->fd.pipe[0]);
		check_close(cmd, cmd->fd.pipe[1]);
	}
	check_close(cmd, cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd, cmd->fd.read);
	else
		check_close(cmd, cmd->fd.tmp);
	ft_putstr_fd("exit\n", 1);
	exit(g_exit);
}
