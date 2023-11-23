/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:15 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:59:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	check_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_fd_hd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nbr)
	{
		check_close(&cmd->fd_hd[i]);
		i++;
	}
}

void	close_fd_child(t_cmd *cmd)
{
	check_close(&cmd->fd.read);
	check_close(&cmd->fd.write);
	check_close(&cmd->fd.other_pipe);
}

void	close_fd_parent(t_cmd *cmd)
{
	check_close(&cmd->fd.read);
	check_close(&cmd->fd.write);
}

void	close_all_fd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->nbr > 0)
	{
		check_close(&cmd->fd.pipe[0]);
		check_close(&cmd->fd.pipe[1]);
	}
	check_close(&cmd->fd.write);
	if (cmd->heredoc == 0)
		check_close(&cmd->fd.read);
	else
		check_close(&cmd->fd.tmp);
	if ((cmd->index != cmd->first) && (cmd->index != cmd->last))
		check_close(&cmd->fd.other_pipe);
	close_fd_hd(cmd);
}
