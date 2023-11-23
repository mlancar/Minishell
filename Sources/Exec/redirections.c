/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:38:01 by malancar          #+#    #+#             */
/*   Updated: 2023/11/24 00:02:26 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	loop_files(t_cmd *cmd, t_lst_file **file, t_lst_cmd *cmd_list)
{
	if ((*file)->infile)
	{		
		if (open_infile(cmd, (*file)->infile) == 0)
			return (0);
	}
	else if ((*file)->outfile)
	{
		if (open_outfile(cmd_list, cmd, (*file)->outfile) == 0)
			return (0);
	}
	else if ((*file)->limiter)
	{
		check_close(&cmd->fd.read);
		cmd->heredoc = 1;
	}
	return (1);
}

int	redirection_one_cmd(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	t_lst_file	*file;

	file = cmd_list->file;
	cmd->heredoc = 0;
	while (file)
	{
		if (loop_files(cmd, &file, cmd_list) == 0)
			return (0);
		file = file->next;
	}
	if (cmd->heredoc == 1)
		cmd->fd.read = cmd->fd_hd[cmd->index];
	else
		check_close(&cmd->fd_hd[cmd->index]);
	return (1);
}

int	heredoc_redirections(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s)
{
	t_lst_file	*tmp_file;
	int			i;

	i = 0;
	while (cmd_list)
	{
		tmp_file = cmd_list->file;
		while (tmp_file)
		{
			if (tmp_file->limiter)
			{
				check_close(&cmd->fd_hd[i]);
				if (open_heredoc(cmd, cmd->fd_hd + i, s, tmp_file->limiter)
					== -1)
				{
					cmd->pid[cmd->index] = -1;
					return (0);
				}
			}
			tmp_file = tmp_file->next;
		}
		cmd_list = cmd_list->next;
		i++;
	}
	return (1);
}
