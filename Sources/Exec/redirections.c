/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:38:01 by malancar          #+#    #+#             */
/*   Updated: 2023/11/19 12:38:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void print_redir(struct s_lst_file *file) {
	if (!file)
		return;
	//printf("infile =%s, outfile = %s,  type = %d, limiter = %s\n", file->infile, file->outfile, file->outfile_type, file->limiter);
	print_redir(file->next);
}

int	redirection_one_cmd(t_lst_cmd *argv, t_cmd *cmd)
{
	//print_redir(argv->file);
	while (argv->file)
	{
		if (argv->file->infile)
		{
			cmd->heredoc = 0;
			if (open_infile(argv, cmd) == 0)
				return (0);
			//printf("infile fdread = %d\n",cmd->fd.read);
			
		}
		else if (argv->file->outfile)
			open_outfile(argv, cmd);
		else
		{
			check_close(cmd, cmd->fd.read);
			cmd->fd.read = -1;
			cmd->heredoc = 1;
		}
		argv->file = argv->file->next;
	}
	if (cmd->heredoc == 1)
	{
		cmd->fd.read = cmd->fd_hd[cmd->index];
		//printf("fdread = %d\n", cmd->fd.read);
	}
	else
		check_close(cmd, cmd->fd_hd[cmd->index]);
	//printf("ici cmd = %s fdread = %d, fdwrite = %d\n", cmd->argv[0], cmd->fd.read, cmd->fd.write);
	return (1);
}

	//boucle remplir heredoc ici ou parsing 
	//lancer buitins avec sans option pas \n ou erreur
int	heredoc_redirections(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s)
{
	t_lst_cmd	*start;
	t_lst_file	*start_file;
	int			i;

	i = 0;
	start = argv;
	while (argv)
	{
		start_file = argv->file;
		while (argv->file)
		{
			if (argv->file->limiter)
			{
				if (open_heredoc(cmd, argv, cmd->fd_hd + i, s) == -1)
					return (-1);
			}
			argv->file = argv->file->next;
		}
		argv->file = start_file;
		argv = argv->next;
		i++;
	}
	argv = start;
	return (1);
}

