/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:15 by malancar          #+#    #+#             */
/*   Updated: 2023/10/30 16:02:26 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_close(t_cmd *cmd, int fd)
{
	(void)cmd;
	if (fd > 2)
	{
		//printf("%s : close fd = %d\n", cmd->argv[0], fd);
		close(fd);
	}
}

void	close_fd_child(t_cmd *cmd)
{
	//dprintf(2, "\nchild, %s : read = %d, write = %d, other_pipe = %d tmp = %d\n", cmd->argv[0], cmd->fd.read, cmd->fd.write, cmd->fd.other_pipe);
	//printf("close child fd \n");
	check_close(cmd, cmd->fd.read);
	check_close(cmd, cmd->fd.write);
	check_close(cmd, cmd->fd.other_pipe);
	// if (cmd->index_pid == cmd->last)
	// {
	// 	//printf("last child %s", cmd->argv[0]);
	// 	check_close(cmd->fd.read);
	// 	check_close(cmd->fd.write);

	// }
	// else if (cmd->index_pid == cmd->first)
	// {
	// 	check_close(cmd->fd.read);
	// 	check_close(cmd->fd.write);
	// }
	// else
	// {
	// 
	// 	//dprintf(2, "\n cmd%d : child : read = %d, write = %d, close = %d tmp = %d\n", cmd->index_pid, cmd->fd.read, cmd->fd.write, cmd->fd.close, cmd->fd.tmp);
	// 	//check_close(cmd->fd.write);
	// 	check_close(cmd->fd.read);
	// 	//check_close(cmd->fd.close);
	// 	check_close(cmd->fd.write);

	// }
}

void	close_fd_parent(t_cmd *cmd)
{
	//printf("\nparent %s : read = %d, write = %d, other pipe = %d\n", cmd->argv[0], cmd->fd.read, cmd->fd.write, cmd->fd.other_pipe);
	//printf("close fd parent \n");
	check_close(cmd, cmd->fd.read);
	//printf("close fd parent\n");
	check_close(cmd, cmd->fd.write);
	//check_close(cmd->fd.close);
	
	if (cmd->index_pid == cmd->first)
	{
		
	}
	//check_close(cmd->fd.close);
	// if (cmd->index_pid == cmd->last)
	// {
	// 	//printf("last parent %s", cmd->argv[0]);
	// 	check_close(cmd->fd.read);
	// 	check_close(cmd->fd.write);
	// 	//check_close(cmd->fd.close);
	// }
	// else
	// {
	// 	//printf("parent %s", cmd->argv[0]);
	// 	check_close(cmd->fd.read);
	// 	check_close(cmd->fd.write);
	// }
}

void	close_fd(t_cmd *cmd)
{
	check_close(cmd, cmd->fd.read);
	check_close(cmd, cmd->fd.write);
	check_close(cmd, cmd->fd.other_pipe);
}
