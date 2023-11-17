/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/11/17 20:10:24 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_infile(t_lst_cmd *argv, t_cmd *cmd)
{
	check_close(cmd, cmd->fd.read);
	cmd->fd.read = open(argv->file->infile, O_RDONLY);
	if (cmd->fd.read == -1)
	{
		g_exit = 1;
		print_error(argv, cmd);
		return (0);
	}
	return (1);
}

void	open_outfile(t_lst_cmd *argv, t_cmd *cmd)
{
	if (argv->file->outfile_type == 0)
	{
		check_close(cmd, cmd->fd.write);
		cmd->fd.write = open(argv->file->outfile, O_RDWR | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
			error_cmd(argv, cmd, 1);
	}
	else
	{
		check_close(cmd, cmd->fd.write);
		cmd->fd.write = open(argv->file->outfile, O_RDWR | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
			error_cmd(argv, cmd, 1);
	}
}
