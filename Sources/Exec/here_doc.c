/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:53:52 by malancar          #+#    #+#             */
/*   Updated: 2023/11/22 22:58:59 by malancar         ###   ########.fr       */
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

void	fill_heredoc(char **read_line, char *limiter, t_cmd *cmd,
		t_lst_cmd *cmd_list)
{
	cmd->files.line++;
	
	(void)cmd_list;
	*read_line = readline("> ");
	if (*read_line == NULL)
	{
		ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
		ft_putnbr_fd(cmd->files.line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (is_limiter(*read_line, limiter) != 0)
	{
		ft_putstr_fd(*read_line, cmd->fd.tmp);
		ft_putstr_fd("\n", cmd->fd.tmp);
	}
}

void	ft_singleton(int mode, t_cmd *cmd, t_lst_cmd *cmd_list,
	t_struct_data *s)
{
	static t_cmd			*static_cmd;
	static t_lst_cmd		*static_cmd_list;
	static t_struct_data	*static_s;

	(void)static_cmd_list;
	if (mode == 0)
	{
		static_cmd = cmd;
		static_cmd_list = cmd_list;
		static_s = s;
	}
	else
	{
		unlink(static_cmd->files.rand_name);
		free(static_cmd->name);
		free(static_cmd->pid);
		free(static_cmd->fd_hd);
		free(static_cmd->env);
		free_parsing(static_s);
		check_close(static_cmd, &static_cmd->fd.tmp);
		check_close(static_cmd, &static_cmd->fd.write);
		check_close(static_cmd, &static_cmd->fd.read);
	}
}

void	child_heredoc(t_struct_data *s, t_cmd *cmd, t_lst_cmd *cmd_list, char *limiter)
{
	char	*read_line;
	int		i;

	i = 0;
	read_line = NULL;
	signal(SIGINT, signal_heredoc);
	fill_heredoc(&read_line, limiter, cmd, cmd_list);
	while (is_limiter(read_line, limiter) != 0)
	{
		free(read_line);
		fill_heredoc(&read_line, limiter, cmd, cmd_list);
	}
	while (i < cmd->nbr)
	{
		check_close(cmd, &cmd->fd_hd[i]);
		i++;
	}
	free(read_line);
	free_and_close_hd(s, cmd);
}

int	fork_heredoc(char *limiter, t_cmd *cmd, t_lst_cmd *cmd_list,
	t_struct_data *s)
{
	int		status;
	int		pid;

	cmd->files.line = 0;
	pid = fork();
	if (pid < 0)
		error_cmd(s, cmd_list, cmd, 1);
	ft_singleton(0, cmd, cmd_list, s);
	if (pid == 0)
		child_heredoc(s, cmd, cmd_list, limiter);
	else
	{
		check_close(cmd, &cmd->fd.tmp);
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) == 130)
		{
			g_exit = 130;
			return (-1);
		}
		return (0);
	}
	return (1);
}
