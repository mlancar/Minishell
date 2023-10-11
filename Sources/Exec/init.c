/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:52:07 by malancar          #+#    #+#             */
/*   Updated: 2023/10/11 15:31:18 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_fd(t_cmd *cmd)
{
	if (cmd->index_pid == cmd->first)
	{
		cmd->fd.read = 0;
		cmd->fd.write = cmd->fd.pipe[1];
		cmd->fd.close = cmd->fd.pipe[0];
	}
	else if (cmd->index_pid == cmd->last)
	{
		cmd->fd.read = cmd->fd.pipe[0];
		cmd->fd.write = 1;
		cmd->fd.close = cmd->fd.pipe[1];
	}
	else if ((cmd->index_pid != cmd->first)
		&& (cmd->index_pid != cmd->last))
	{
		cmd->fd.read = cmd->fd.previous;
		cmd->fd.write = cmd->fd.pipe[1];
		cmd->fd.close = cmd->fd.pipe[0];
	}
}

void	set_files(t_lst_cmd *argv, t_cmd *cmd)
{
	if (argv->file)
	{
		if (argv->file->limiter)
			cmd->if_here_doc = 1;
		else
			cmd->if_here_doc = 0;
		if (argv->file->infile)
			open_infile(argv, cmd);
		if (argv->file->outfile)
			open_outfile(argv, cmd);
	}
}

void	init_struct(t_cmd *cmd, t_lst_cmd *argv)
{
	
	cmd->nbr = list_size(argv);
	cmd->index = 0;
	cmd->index_pid = 0;
	cmd->first = 0;
	cmd->path = NULL;
	cmd->last = cmd->nbr - 1;
	// set_fd(cmd);
	// set_files(argv, cmd);
}