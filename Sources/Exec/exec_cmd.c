/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:27:01 by malancar          #+#    #+#             */
/*   Updated: 2023/11/22 23:01:14 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_child(t_cmd *cmd, t_struct_data *s, t_lst_cmd *cmd_list)
{
	int	i;

	i = 0;
	if (check_builtins(cmd) == 1)
	{
		if (exec_builtins(cmd, s) == 0)
			error_cmd(s, cmd_list, cmd, 126);
		close_fd_child(cmd);
		free_exec(cmd);
		free_parsing(s);
		g_exit = 0;
		exit(EXIT_SUCCESS);
	}
	else
	{
		while (i < cmd->nbr)
		{
			check_close(cmd, &cmd->fd_hd[i]);
			i++;
		}
		if (execve(cmd->path, cmd->name, cmd->env))
			error_exec(s, cmd, 126);
	}
}

void	exec_cmd(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s)
{
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		error_cmd(s, cmd_list, cmd, 1);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		restore_signal();
		if (check_builtins(cmd) == 0)
		{
			if (dup2(cmd->fd.read, 0) == -1 || dup2(cmd->fd.write, 1) == -1)
				error_cmd(s, cmd_list, cmd, 126);
			close_fd_child(cmd);
			check_close(cmd, &cmd->fd.tmp);
			//check_close(cmd, &cmd->fd.tmp);
		}
		exec_child(cmd, s, cmd_list);
	}
	else
		close_fd_parent(cmd);
}

int	exec(t_struct_data *s, t_cmd *cmd, t_lst_cmd *cmd_list)
{
	if (check_builtins(cmd) == 1 && cmd->nbr == 1)
	{
		one_cmd_builtin(cmd, s, cmd_list);
		return (0);
	}
	else
	{
		exec_cmd(cmd_list, cmd, s);
		return (1);
	}
}

void	one_cmd_builtin(t_cmd *cmd, t_struct_data *s, t_lst_cmd *cmd_list)
{
	if (exec_builtins(cmd, s) == 0)
		error_cmd(s, cmd_list, cmd, 126);
	close_fd_parent(cmd);
}
