/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/11/17 19:57:06 by malancar         ###   ########.fr       */
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
		//printf("cc limiter %c\n", str[i]);
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
	//printf("getrandname : fd tmp = %d\n", cmd->fd.tmp);
	check_close(cmd, cmd->fd.tmp);
	//printf("fdtmp = %d\n", cmd->fd.tmp);
	cmd->fd.tmp = open(cmd->files.rand_name, O_WRONLY | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
	if (cmd->fd.tmp == -1)
		free_and_exit(cmd, 1);
}

void	fill_here_doc(char **read_line, char *limiter, t_cmd *cmd,
t_lst_cmd *argv)
{
	cmd->files.line++;
	write(1, "> ", 2);
	*read_line = get_next_line(0, 0);
	if (*read_line == NULL)
	{
		ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
		ft_putnbr_fd(cmd->files.line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(argv->file->limiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (is_limiter(*read_line, limiter) != 0)
		ft_putstr_fd(*read_line, cmd->fd.tmp);
}

void	signal_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		g_exit = 130;
		ft_putstr_fd("\n", 0);
		exit(g_exit);
	}
}

void	here_doc(char *limiter, t_cmd *cmd, t_lst_cmd *argv)
{
	char	*read_line;
	int		status;
	//int		pid;

	//cmd->fd.tmp = 0;
	cmd->files.line = 0;
	cmd->pid[cmd->index_pid] = fork();
	//printf("pid heredoc= %d\n", cmd->pid[cmd->index_pid]);
	if (cmd->pid[cmd->index_pid] < 0)
		error_cmd(argv, cmd, 1);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		//get_rand_name(cmd);
		signal(SIGINT, signal_here_doc);
		//get_rand_name(cmd);
		fill_here_doc(&read_line, limiter, cmd, argv);
		while (is_limiter(read_line, limiter) != 0)
		{
			free(read_line);
			fill_here_doc(&read_line, limiter, cmd, argv);
		}
		get_next_line(0, 1);
		free(read_line);
		// printf("fd.read = %d\n", cmd->fd.read);
		// printf("fd.write = %d\n", cmd->fd.write);
		//printf("fd.tmp = %d\n", cmd->fd.tmp);
		check_close(cmd, cmd->fd.write);
		//check_close(cmd, cmd->fd.read);
		check_close(cmd, cmd->fd.tmp);
		//printf("cc ici\n");
		
		//unlink(cmd->files.rand_name);			
		exit(EXIT_SUCCESS);
		//printf("cc\n");
	}
	else
	{
		//printf("pid heredoc= %d\n", cmd->pid[cmd->index_pid]);
		waitpid(cmd->pid[cmd->index_pid], &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) == 130)
			g_exit = 130;
	}
}
