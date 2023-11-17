/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:15 by malancar          #+#    #+#             */
/*   Updated: 2023/11/17 20:10:52 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_close(t_cmd *cmd, int fd)
{
	(void)cmd;
	if (fd > 2)
	{
		//printf("check fd.tmp = %d\n", cmd->fd.tmp);
		//printf("check fd= %d\n", fd);
		close(fd);
		//fd = -1;
	}
}

void	close_fd_child(t_cmd *cmd)
{
	check_close(cmd, cmd->fd.read);
	check_close(cmd, cmd->fd.write);
	check_close(cmd, cmd->fd.other_pipe);
}

void	close_fd_parent(t_cmd *cmd)
{
	check_close(cmd, cmd->fd.read);
	check_close(cmd, cmd->fd.write);
}

void	close_fd(t_cmd *cmd)
{
	check_close(cmd, cmd->fd.read);
	check_close(cmd, cmd->fd.write);
	check_close(cmd, cmd->fd.other_pipe);
}
