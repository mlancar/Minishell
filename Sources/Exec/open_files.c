/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/10/11 15:31:18 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_lst_cmd *argv, t_cmd *cmd)
{
	cmd->fd.read = open(argv->file->infile, O_RDONLY);
	if (cmd->fd.read == -1)
		perror("open");
}

void	open_outfile(t_lst_cmd *argv, t_cmd *cmd)
{
	if (cmd->if_here_doc == 1)
	{
		// cmd->files.out = open(argv->file->outfile, O_RDWR | O_APPEND | O_CREAT, S_IRUSR
		// 		| S_IWUSR | S_IRGRP | S_IROTH);
		// if (cmd->files.out == -1)
		// {
		// 	perror("open");
		// 	exit(EXIT_FAILURE);
		// }
		printf("here_doc\n");
	}
	else
	{
		printf("cc\n");
		cmd->fd.write = open(argv->file->outfile, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		printf("cmd->fd.write = %d\n", cmd->fd.write);
	}
}
