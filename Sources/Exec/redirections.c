/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:38:01 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 20:21:45 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redirection_one_cmd(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	t_lst_file	*file;

	file = cmd_list->file;
	cmd->heredoc = 0;
	while (file)
	{
		if (file->infile)
		{
			if (open_infile(cmd, file->infile) == 0)
				return (0);
		}
		else if (file->outfile)
		{
			if (open_outfile(cmd_list, cmd, file->outfile) == 0)
				return (0);
		}
		else if (file->limiter)
		{
			check_close(cmd, &cmd->fd.read);
			cmd->heredoc = 1;
		}
		file = file->next;
	}
	if (cmd->heredoc == 1)
		cmd->fd.read = cmd->fd_hd[cmd->index_pid];
	else
		check_close(cmd, &cmd->fd_hd[cmd->index_pid]);
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
				check_close(cmd, &cmd->fd_hd[i]);
				if (open_heredoc(cmd, cmd->fd_hd + i, s, tmp_file->limiter) == -1)
				{
					cmd->pid[cmd->index_pid] = -1;
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
