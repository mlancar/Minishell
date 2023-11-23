/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:13:28 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:59:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_infile(t_cmd *cmd, char *infile)
{
	cmd->heredoc = 0;
	check_close(&cmd->fd.read);
	cmd->fd.read = open(infile, O_RDONLY);
	if (cmd->fd.read == -1)
	{
		g_exit = 1;
		error_open_file(cmd, infile, NULL);
		return (0);
	}
	return (1);
}

int	open_outfile(t_lst_cmd *cmd_list, t_cmd *cmd, char *outfile)
{
	if (cmd_list->file->outfile_type == 0)
	{
		check_close(&cmd->fd.write);
		cmd->fd.write = open(outfile, O_RDWR | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
		{
			error_open_file(cmd, NULL, outfile);
			return (0);
		}
	}
	else
	{
		check_close(&cmd->fd.write);
		cmd->fd.write = open(outfile, O_RDWR | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (cmd->fd.write == -1)
		{
			error_open_file(cmd, NULL, outfile);
			return (0);
		}
	}
	return (1);
}

int	open_heredoc(t_cmd *cmd, int *fd, t_struct_data *s, char *limiter)
{
	cmd->heredoc = 1;
	get_rand_name(s, cmd);
	cmd->pid[cmd->index] = -1;
	if (fork_heredoc(limiter, cmd, s->cmd, s) == -1)
		return (-1);
	*fd = open(cmd->files.rand_name, O_RDONLY);
	if (*fd == -1)
		free_and_exit(s, cmd, 1);
	unlink(cmd->files.rand_name);
	return (1);
}

void	get_rand_name(t_struct_data *s, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->fd.tmp = open("/dev/random", O_RDONLY);
	if (cmd->fd.tmp == -1)
		free_and_exit(s, cmd, 1);
	if (read(cmd->fd.tmp, cmd->files.rand_name, 6) == -1)
		free_and_exit(s, cmd, 1);
	cmd->files.rand_name[6] = '\0';
	i = 0;
	while (i < 6)
	{
		cmd->files.rand_name[i] = cmd->files.rand_name[i] % 26;
		if (cmd->files.rand_name[i] < 0)
			cmd->files.rand_name[i] = cmd->files.rand_name[i] + 26;
		cmd->files.rand_name[i] = cmd->files.rand_name[i] + 97;
		i++;
	}
	check_close(&cmd->fd.tmp);
	cmd->fd.tmp = open(cmd->files.rand_name, O_WRONLY | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
	if (cmd->fd.tmp == -1)
		free_and_exit(s, cmd, 1);
}
