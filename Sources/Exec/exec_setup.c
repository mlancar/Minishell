/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:53:05 by malancar          #+#    #+#             */
/*   Updated: 2023/11/22 23:09:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	setup_exec(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd)
{
	int	check_cmd;

	init_fd(cmd);
	if (redirection_one_cmd(cmd_list, cmd) == 0)
	{
		close_fd_parent(cmd);
		cmd->pid[cmd->index_pid] = -1;
		return (0);
	}
	check_cmd = is_command_valid(cmd_list, cmd);
	if (check_cmd == -1)
	{
		close_fd_parent(cmd);
		return (0);
	}
	else if (check_cmd == 0)
	{
		cmd->pid[cmd->index_pid] = -1;
		error_access_cmd(s, cmd_list, cmd);
		return (0);
	}
	return (1);
}

void	pipe_cmd(t_struct_data *s, t_cmd *cmd, t_lst_cmd *cmd_list)
{
	if (cmd->nbr != 1)
		cmd->fd.previous = cmd->fd.pipe[0];
	if ((cmd->index_pid != cmd->first)
		&& (cmd->index_pid != cmd->last))
	{
		if (pipe(cmd->fd.pipe) == -1)
			error_cmd(s, cmd_list, cmd, 1);
	}
}

void	loop_exec(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s)
{
	int	setup;

	ignore_signal();
	if (heredoc_redirections(cmd_list, cmd, s) == 0)
		return ;	
	if (cmd->nbr != 1 && pipe(cmd->fd.pipe) == -1)
		error_cmd(s, cmd_list, cmd, 1);
	while (cmd->index_pid < cmd->nbr)
	{
		convert_list(cmd, cmd_list);
		pipe_cmd(s, cmd, cmd_list);
		setup = setup_exec(s, cmd_list, cmd);
		if (setup == 1)
		{
			if (exec(s, cmd, cmd_list) == 0)
				return ;
		}
		else if (setup == -1)
			return ;
		cmd->index_pid++;
		if (check_builtins(cmd) == 0)
			free_and_set(cmd, &cmd->path);
		if (cmd->name[0] == NULL)
			check_close(cmd, &cmd->fd.tmp);
		if (cmd_list != NULL)
			cmd_list = cmd_list->next;
	}
}

int	start_exec(t_lst_cmd *cmd_list, t_struct_data *s)
{
	t_cmd	cmd;

	convert_list_env(&cmd, s);
	init_struct(&cmd, cmd_list);
	loop_exec(cmd_list, &cmd, s);
	if (check_builtins(&cmd) == 1 && cmd.nbr == 1)
	{
		free_exec(&cmd);
		return (0);
	}
	wait_cmd(&cmd);
	close_fd_hd(&cmd);
	free_exec(&cmd);
	return (0);
}
