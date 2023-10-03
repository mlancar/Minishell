/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/09/27 14:13:15 by malancar         ###   ########.fr       */
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

void	get_rand_name(t_pipex *pipex_cmd)
{
	int	i;

	i = 0;
	pipex_cmd->fd_tmp = open("/dev/random", O_RDONLY);
	if (pipex_cmd->fd_tmp == -1)
		free_and_exit("open", pipex_cmd);
	if (read(pipex_cmd->fd_tmp, pipex_cmd->rand_name, 6) == -1)
		free_and_exit("open", pipex_cmd);
	pipex_cmd->rand_name[6] = '\0';
	i = 0;
	while (i < 6)
	{
		pipex_cmd->rand_name[i] = pipex_cmd->rand_name[i] % 26;
		if (pipex_cmd->rand_name[i] < 0)
			pipex_cmd->rand_name[i] = pipex_cmd->rand_name[i] + 26;
		pipex_cmd->rand_name[i] = pipex_cmd->rand_name[i] + 97;
		i++;
	}
	close(pipex_cmd->fd_tmp);
	pipex_cmd->fd_tmp = open(pipex_cmd->rand_name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP);
	if (pipex_cmd->fd_tmp == -1)
		free_and_exit("open", pipex_cmd);
}

void	fill_here_doc(char **read_line, char *limiter, t_pipex *pipex_cmd)
{
	int	nbr_pipe;

	nbr_pipe = pipex_cmd->max - 1;
	while (nbr_pipe > 0)
	{
		write(1, "pipe ", 5);
		nbr_pipe--;
	}
	write(1, "here_doc> ", 10);
	*read_line = get_next_line(0, 0);
	if (*read_line == NULL)
		write(2, "\nwarning: here-doc delimited by end-of-file\n", 45);
	if (is_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, pipex_cmd->fd_tmp);
}

void	open_and_fill_here_doc(t_pipex *pipex_cmd, char *limiter)
{
	char	*read_line;

	get_rand_name(pipex_cmd);
	fill_here_doc(&read_line, limiter, pipex_cmd);
	while (is_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_here_doc(&read_line, limiter, pipex_cmd);
	}
	get_next_line(0, 1);
	free(read_line);
	close(pipex_cmd->fd_tmp);
}

void	here_doc(char *limiter, t_pipex *pipex_cmd)
{
	pipex_cmd->fd_tmp = 0;
	open_and_fill_here_doc(pipex_cmd, limiter);
	pipex_cmd->fd_tmp = open(pipex_cmd->rand_name, O_RDONLY);
	if (pipex_cmd->fd_tmp == -1)
		free_and_exit("open", pipex_cmd);
}
