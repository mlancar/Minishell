/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:52:07 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 21:07:06 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_fd(t_cmd *cmd)
{
	if (cmd->nbr == 1)
	{
		cmd->fd.read = 0;
		cmd->fd.write = 1;
		cmd->fd.other_pipe = -1;
	}
	else if (cmd->index_pid == cmd->first)
	{
		cmd->fd.read = 0;
		cmd->fd.write = cmd->fd.pipe[1];
		cmd->fd.other_pipe = cmd->fd.pipe[0];
	}
	else if (cmd->index_pid == cmd->last)
	{
		cmd->fd.read = cmd->fd.pipe[0];
		cmd->fd.write = 1;
		cmd->fd.other_pipe = cmd->fd.pipe[1];
	}
	else if ((cmd->index_pid != cmd->first)
		&& (cmd->index_pid != cmd->last))
	{
		cmd->fd.read = cmd->fd.previous;
		cmd->fd.write = cmd->fd.pipe[1];
		cmd->fd.other_pipe = cmd->fd.pipe[0];
	}
}

void	init_struct(t_cmd *cmd, t_lst_cmd *cmd_list)
{
	cmd->nbr = list_size(cmd_list);
	cmd->fd_hd = ft_calloc(cmd->nbr, sizeof(int));
	cmd->index = 0;
	cmd->index_pid = 0;
	cmd->first = 0;
	cmd->path = NULL;
	cmd->last = cmd->nbr - 1;
	cmd->heredoc = 0;
	cmd->fd.tmp = -1;
	cmd->fd.read = -1;
	cmd->fd.write = -1;
	cmd->fd.pipe[0] = -1;
	cmd->fd.pipe[1] = -1;
	cmd->name = NULL;
	cmd->pid = malloc(sizeof(pid_t) * cmd->nbr);
	if (!cmd->pid)//pas sur
	{
		write(1, "pid error\n", 10);
		return ;
	}
}
