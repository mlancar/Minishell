/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:52:07 by malancar          #+#    #+#             */
/*   Updated: 2023/11/17 19:37:06 by malancar         ###   ########.fr       */
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

int	set_redirections(t_lst_cmd *argv, t_cmd *cmd)
{
	if (argv->file)
	{
		// if (argv->file->limiter)
		// 	cmd->if_here_doc = 1;
		// else
		// 	cmd->if_here_doc = 0;
		if (argv->file->infile)
		{
			if (open_infile(argv, cmd) == 0)
				return (0);
		}
		if (argv->file->outfile)
		{
			open_outfile(argv, cmd);
			//printf("ICI LA VRAIEMNT ICI set redir : fd.write = %d\n", cmd->fd.write);
		}
	}
	//printf("avant return fdwrite = %d\n", cmd->fd.write);
	return (1);
}

void	init_struct(t_cmd *cmd, t_lst_cmd *argv)
{
	cmd->nbr = list_size(argv);
	cmd->index = 0;
	cmd->index_pid = 0;
	cmd->first = 0;
	cmd->path = NULL;
	cmd->last = cmd->nbr - 1;
	cmd->if_here_doc = 0;
	cmd->fd.tmp = -1;
	cmd->argv = NULL;
}
