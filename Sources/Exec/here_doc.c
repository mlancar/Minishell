/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/10/13 17:08:08 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_limiter(char *str, char *limiter)
{
	int	i;

	i = 0;
	if (!str || !limiter)
		return (0);
	while ((str[i] && limiter[i]))
	{
		if (str[i] != limiter[i])
			return (-1);
		i++;
	}
	if (str[i] == '\n' && limiter[i] == '\0')
		return (0);
	return (str[i] - limiter[i]);
}

void	get_rand_name(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->fd.tmp = open("/dev/random", O_RDONLY);
	if (cmd->fd.tmp == -1)
		free_and_exit("open", cmd);
	if (read(cmd->fd.tmp, cmd->files.rand_name, 6) == -1)
		free_and_exit("open", cmd);
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
	check_close(cmd->fd.tmp);
	cmd->fd.tmp = open(cmd->files.rand_name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP);
	if (cmd->fd.tmp == -1)
		free_and_exit("open", cmd);
}

void	fill_here_doc(char **read_line, char *limiter, t_cmd *cmd)
{
	write(1, "here_doc> ", 10);
	*read_line = get_next_line(0, 0);
	if (*read_line == NULL)
		write(2, "\nwarning: here-doc delimited by end-of-file\n", 45);
	if (is_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, cmd->fd.tmp);
}

void	open_and_fill_here_doc(t_cmd *cmd, char *limiter)
{
	char	*read_line;

	get_rand_name(cmd);
	fill_here_doc(&read_line, limiter, cmd);
	while (is_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_here_doc(&read_line, limiter, cmd);
	}
	get_next_line(0, 1);
	free(read_line);
	check_close(cmd->fd.tmp);
}

void	here_doc(char *limiter, t_cmd *cmd)
{
	cmd->fd.tmp = 0;
	open_and_fill_here_doc(cmd, limiter);
	cmd->fd.tmp = open(cmd->files.rand_name, O_RDONLY);
	if (cmd->fd.tmp == -1)
		free_and_exit("open", cmd);
}
