/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 19:00:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		free_and_exit(cmd, 1);
	if (read(cmd->fd.tmp, cmd->files.rand_name, 6) == -1)
		free_and_exit(cmd, 1);
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
	//dprintf(2, "fd tmp = %d\n", cmd->fd.tmp);
	check_close(cmd, cmd->fd.tmp);
	cmd->fd.tmp = open(cmd->files.rand_name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
			| S_IWUSR | S_IRGRP);
	if (cmd->fd.tmp == -1)
		free_and_exit(cmd, 1);
}

void	fill_here_doc(char **read_line, char *limiter, t_cmd *cmd, t_lst_cmd *argv)
{
	int	line;

	line = 0;
	write(1, "> ", 2);
	*read_line = get_next_line(0, 0);
	line++;
	
	if (*read_line == NULL)
	{
		ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
		//add line
		//ft_putstr_fd()
		ft_putstr_fd("delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(argv->file->limiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (is_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, cmd->fd.tmp);
}

void	here_doc(char *limiter, t_cmd *cmd, t_lst_cmd *argv)
{
	char	*read_line;
	
	cmd->fd.tmp = 0;
	get_rand_name(cmd);
	fill_here_doc(&read_line, limiter, cmd, argv);
	while (is_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_here_doc(&read_line, limiter, cmd, argv);
	}
	get_next_line(0, 1);
	free(read_line);
	check_close(cmd, cmd->fd.tmp);
	cmd->fd.tmp = open(cmd->files.rand_name, O_RDONLY);
	if (cmd->fd.tmp == -1)
		free_and_exit(cmd, 1);
}
