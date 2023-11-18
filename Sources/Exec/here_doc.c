/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/11/18 23:24:04 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_here_doc(t_lst_cmd *argv, t_cmd *cmd)
{
	if (argv->file)
	{
		if (argv->file->limiter)
		{
			cmd->heredoc = 1;
		}
		else
			cmd->heredoc = 0;
	}
	return (1);
}

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
	check_close(cmd, cmd->fd.tmp);
	cmd->fd.tmp = open(cmd->files.rand_name, O_WRONLY | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
	if (cmd->fd.tmp == -1)
		free_and_exit(cmd, 1);
}

void	fill_heredoc(char **read_line, char *limiter, t_cmd *cmd,
t_lst_cmd *argv)
{
	cmd->files.line++;
	dprintf(2, "fdtmp %d, fdwrite %d, fdread%d\n", cmd->fd.tmp, cmd->fd.write, cmd->fd.read);
	*read_line = readline("> ");
	dprintf(2, "fdtmp %d, fdwrite %d, fdread%d\n", cmd->fd.tmp, cmd->fd.write, cmd->fd.read);
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

void	ft_singleton(int mode, t_cmd *cmd, t_lst_cmd *argv, t_struct_data *s)
{
	static t_cmd			*static_cmd;
	static t_lst_cmd		*static_argv;
	static t_struct_data	*static_s;
	
	if (mode == 0)
	{
		static_cmd = cmd;
		static_argv = argv;
		static_s = s;
	}
	else
	{
		free(static_cmd->argv);
		free(static_cmd->pid);
		free(static_cmd->fd_hd);
		free(static_cmd->env);
		free_all(static_s);
		unlink(cmd->files.rand_name);
		check_close(static_cmd, static_cmd->fd.tmp);
		check_close(static_cmd, static_cmd->fd.write);
		check_close(static_cmd, static_cmd->fd.read);
	}
}

void	signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		ft_singleton(1, NULL, NULL, NULL);
		get_next_line(0, 1);
		exit(130);
	}
}

int	fork_heredoc(char *limiter, t_cmd *cmd, t_lst_cmd *argv, t_struct_data *s)
{
	char	*read_line;
	int		status;
	int		pid;

	cmd->files.line = 0;
	read_line = NULL;
	pid = fork();
	if (pid < 0)
		error_cmd(argv, cmd, 1);
	ft_singleton(0, cmd, argv, s);
	if (pid == 0)
	{
		signal(SIGINT, signal_heredoc);
		fill_heredoc(&read_line, limiter, cmd, argv);
		dprintf(2, "fdtmp %d, fdwrite %d, fdread%d\n", cmd->fd.tmp, cmd->fd.write, cmd->fd.read);
		while (is_limiter(read_line, limiter) != 0)
		{
			free(read_line);
			fill_heredoc(&read_line, limiter, cmd, argv);
		}
		free(read_line);
		free(cmd->fd_hd);
		free(cmd->pid);
		free(cmd->env);
		free(cmd->path);
		free(cmd->argv);
		free_all(s);
		check_close(cmd, cmd->fd.write);
		check_close(cmd, cmd->fd.tmp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		check_close(cmd, cmd->fd.tmp);
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) == 130)
		{
			
			g_exit = 130;
			return (-1);
		}
		
		return (0);
	}
}

int	open_heredoc(t_cmd *cmd, t_lst_cmd *argv, int *fd, t_struct_data *s)
{
	cmd->heredoc = 1;
	get_rand_name(cmd);
	cmd->pid[cmd->index_pid] = -1;
	if (fork_heredoc(argv->file->limiter, cmd, argv, s) == -1)
		return (-1);
	*fd = open(cmd->files.rand_name, O_RDONLY);
	if (*fd == -1)
		free_and_exit(cmd, 1);//pas exit process principal?
	unlink(cmd->files.rand_name);
	return (1);
}
