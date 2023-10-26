/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:15 by malancar          #+#    #+#             */
/*   Updated: 2023/10/26 19:01:40 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_fd_child(t_lst_cmd *argv, t_cmd *cmd)
{
	(void)argv;
	if (cmd->index_pid == cmd->last)
	{
		//dprintf(2, "\n last cmd%d : child : read = %d, write = %d, close = %d tmp = %d\n", cmd->index_pid, cmd->fd.read, cmd->fd.write, cmd->fd.close, cmd->fd.tmp);
		check_close(cmd->fd.read);
		check_close(cmd->fd.write);
	}
	else
	{
		//dprintf(2, "\n cmd%d : child : read = %d, write = %d, close = %d tmp = %d\n", cmd->index_pid, cmd->fd.read, cmd->fd.write, cmd->fd.close, cmd->fd.tmp);
		check_close(cmd->fd.write);
		check_close(cmd->fd.read);
		check_close(cmd->fd.close);
	}
}

void	close_fd_parent(t_lst_cmd *argv, t_cmd *cmd)
{
	(void)argv;
	//printf("\nparent : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->index_pid == cmd->last)
	{
		check_close(cmd->fd.read);
		check_close(cmd->fd.write);
		check_close(cmd->fd.close);
	}
	else
	{
		check_close(cmd->fd.read);
		check_close(cmd->fd.write);
	}
}
