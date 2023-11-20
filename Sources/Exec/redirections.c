/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:38:01 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 00:44:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void print_redir(struct s_lst_file *file) {
	if (!file)
		return;
	//printf("infile =%s, outfile = %s,  type = %d, limiter = %s\n", file->infile, file->outfile, file->outfile_type, file->limiter);
	print_redir(file->next);
}

int	redirection_one_cmd(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd)
{
	t_lst_file	*start;
	
	start = cmd_list->file;
	cmd->heredoc = 0;
	while (cmd_list->file)
	{
		if (cmd_list->file->infile)
		{
			cmd->heredoc = 0;
			if (open_infile(cmd_list, cmd) == 0)
				return (0);
		}
		else if (cmd_list->file->outfile)
			open_outfile(s, cmd_list, cmd);
		else
		{
			check_close(cmd, &cmd->fd.read);
			cmd->fd.read = -1;
			cmd->heredoc = 1;
		}
		cmd_list->file = cmd_list->file->next;
	}
	if (cmd->heredoc == 1)
		cmd->fd.read = cmd->fd_hd[cmd->index];
	else
		check_close(cmd, &cmd->fd_hd[cmd->index]);
	cmd_list->file = start;
	return (1);
}

int	heredoc_redirections(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s)
{
	t_lst_cmd	*start;
	t_lst_file	*start_file;
	int			i;

	i = 0;
	start = cmd_list;
	while (cmd_list)
	{
		start_file = cmd_list->file;
		while (cmd_list->file)
		{
			if (cmd_list->file->limiter)
			{
				check_close(cmd, &cmd->fd_hd[i]);
				if (open_heredoc(cmd, cmd_list, cmd->fd_hd + i, s) == -1)
				{
					cmd->pid[cmd->index_pid] = -1;
					return (0);
				}
			}
			cmd_list->file = cmd_list->file->next;
		}
		cmd_list->file = start_file;
		cmd_list = cmd_list->next;
		i++;
	}
	cmd_list = start;
	return (1);
}

