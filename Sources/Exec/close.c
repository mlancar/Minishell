/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:15 by malancar          #+#    #+#             */
/*   Updated: 2023/11/20 19:16:12 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_close(t_cmd *cmd, int *fd)
{
	(void)cmd;
	//printf("%s close fd = %d\n", cmd->name[0], *fd);
	if (*fd > 2)
		close(*fd);
	*fd = -1;
}

void	close_fd_hd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->nbr)
	{
		check_close(cmd, &cmd->fd_hd[i]);
		i++;
	}
}

void	close_fd_child(t_cmd *cmd)
{
	//printf("child\n");
	check_close(cmd, &cmd->fd.read);
	check_close(cmd, &cmd->fd.write);
	check_close(cmd, &cmd->fd.other_pipe);
}

void	close_fd_parent(t_cmd *cmd)
{
	//printf("parent\n");
	//if (cmd->nbr == 2)
	//check_close(cmd, &cmd->fd.other_pipe);
	check_close(cmd, &cmd->fd.read);
	check_close(cmd, &cmd->fd.write);
}

void	close_fd(t_cmd *cmd)
{
	
	check_close(cmd, &cmd->fd.write);
	check_close(cmd, &cmd->fd.other_pipe);
}
