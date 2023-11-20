/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/11/20 17:06:47 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_infile(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	cmd->heredoc = 0;
	check_close(cmd, &cmd->fd.read);
	cmd->fd.read = open(cmd_list->file->infile, O_RDONLY);
	if (cmd->fd.read == -1)
	{
		g_exit = 1;
		print_error(cmd_list, cmd);
		return (0);
	}
	return (1);
}

void	open_outfile(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (cmd_list->file->outfile_type == 0)
	{
		check_close(cmd, &cmd->fd.write);
		cmd->fd.write = open(cmd_list->file->outfile, O_RDWR | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
			error_cmd(s, cmd_list, cmd, 1);
	}
	else
	{
		check_close(cmd, &cmd->fd.write);
		cmd->fd.write = open(cmd_list->file->outfile, O_RDWR | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
			error_cmd(s, cmd_list, cmd, 1);
	}
}
