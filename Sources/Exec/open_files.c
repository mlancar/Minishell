/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/10/20 19:32:15 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_lst_cmd *argv, t_cmd *cmd)
{
	check_close(cmd->fd.read);
	cmd->fd.read = open(argv->file->infile, O_RDONLY);
	if (cmd->fd.read == -1)
		perror("open");
}

void	open_outfile(t_lst_cmd *argv, t_cmd *cmd)
{
	if (argv->file->outfile_type == 0)
	{
		check_close(cmd->fd.write);
		cmd->fd.write = open(argv->file->outfile, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}	
	}
	else
	{
		check_close(cmd->fd.write);
		cmd->fd.write = open(argv->file->outfile, O_RDWR | O_APPEND | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}	
	}
}
