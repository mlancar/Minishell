/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/09/27 14:13:42 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_pipex *pipex_cmd, char *first_arg)
{
	pipex_cmd->infile = open(first_arg, O_RDONLY);
	if (pipex_cmd->infile == -1)
		perror("open");
}

void	open_outfile(t_pipex *pipex_cmd, char *last_arg)
{
	if (pipex_cmd->if_here_doc == 1)
	{
		pipex_cmd->outfile = open(last_arg, O_RDWR | O_APPEND | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (pipex_cmd->outfile == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pipex_cmd->outfile = open(last_arg, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		if (pipex_cmd->outfile == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
	}
}
