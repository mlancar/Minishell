/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:50:22 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 18:42:52 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

// Note: It is also to taken into consideration that an exit code
// with a value greater than 255 returns an exit code modulo 256.
// For Example: If we execute a statement exit(9999)
// then it will execute exit(15) as 9999%256 = 15.

int		check_exit_code(t_cmd *cmd, int exit_code)
{
	(void)cmd;
	while (exit_code > 255)
		exit_code = exit_code % 256;
	while (exit_code < 0)
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

int		is_arg_numeric(t_cmd *cmd)
{
	int	i;

	i  = 0;
	while (cmd->argv[1][i])
	{
		while (cmd->argv[1][i] && (cmd->argv[1][i] >= '0' && cmd->argv[1][i] <= '9'))
			i++;
		if (cmd->argv[1][i] && (cmd->argv[1][i] != '-' || cmd->argv[1][i] != '+'))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minihsell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int		builtin_exit(t_lst_cmd *argv, t_cmd *cmd)
{
	int	exit_code;
	
	if (is_arg_numeric(cmd) == 0)
		free_and_exit(cmd, 2);
	exit_code = ft_atoi(cmd->argv[1]);
	if (builtin_arg_nbr(cmd) == -1)
	{
		ft_putstr_fd("exit\n", 2);
		return (error_builtins(cmd), -1);
	}
	exit_code = check_exit_code(cmd, exit_code);
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
	exit(exit_code);
}
