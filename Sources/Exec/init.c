/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:52:07 by malancar          #+#    #+#             */
/*   Updated: 2023/10/05 19:03:19 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_files(t_lst_argv *argv, t_cmd *cmd)
{
	if (argv->file)
	{
		if (argv->file->limiter)
			cmd->if_here_doc = 1;
		else
			cmd->if_here_doc = 0;
		if (argv->file->infile)
			open_infile(argv, cmd);
		else
			cmd->files.in = 0;
		if (argv->file->outfile)
			open_outfile(argv, cmd);
		else
			cmd->files.out = 1;
	}
	else if (argv->file == NULL)
	{
		cmd->files.in = 0;
		cmd->files.out = 1;
	}
}

void	init_struct(t_cmd *cmd, t_lst_argv *argv)
{
	init_files(argv, cmd);
	cmd->nbr = list_size(argv);
	cmd->index = 0;
	cmd->index_pid = 0;
	cmd->first = 0;
	cmd->path = NULL;
	cmd->last = cmd->nbr - 1;
}