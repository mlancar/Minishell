/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/11/15 18:57:41 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	redirections(t_lst_cmd *argv, t_cmd *cmd)
{
	//boucle remplir heredoc ici ou parsing 
	//lancer buitins avec sans option pas \n ou erreur
	while (argv->file)
	{
		if (set_redirections(argv, cmd) == 0)
			return (0);
		if (cmd->if_here_doc == 1)
		{
			//get_rand_name(cmd);
			here_doc(argv->file->limiter, cmd, argv);
			if (g_exit == 130)
				return (-1);
			check_close(cmd, cmd->fd.read);
			cmd->fd.read = cmd->fd.tmp;
			unlink(cmd->files.rand_name);
		}
		argv->file = argv->file->next;
	}
	return (1);
}

void	free_in_builtin(t_cmd *cmd)
{
	free(cmd->path);
	free(cmd->pid);
	free(cmd->argv);
	free(cmd->env);
}

void	one_cmd_and_builtin(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv)
{
	(void)s;
	if (exec_builtins(cmd, s, argv) == 0)
		error_cmd(argv, cmd, 126);
	close_fd_parent(cmd);
	//free_in_builtin(cmd);
	g_exit = 0;
	return ;
}

void	exec_cmd(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv)
{
	if (check_builtins(cmd) == 1)
	{
		if (exec_builtins(cmd, s, argv) == 0)
			error_cmd(argv, cmd, 126);
		close_fd(cmd);
		//tout free
		free_in_builtin(cmd);
		g_exit = 0;
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (execve(cmd->path, cmd->argv, cmd->env))
			error_cmd(argv, cmd, 126);
	}
}

int	setup_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s)
{
	int	redir;
	
	init_fd(cmd);
	redir = redirections(argv, cmd);
	if (redir == 0)
	{
		cmd->pid[cmd->index_pid] = -1;
		return (0);
	}
	else if (redir == -1)
		return (-1);
	if (check_command(argv, cmd) == -1)
	{
		cmd->pid[cmd->index_pid] = -1;
		return (0);
	}
	else if (check_command(argv, cmd) == 0)
	{
		cmd->pid[cmd->index_pid] = -1;
		return (error_access_cmd(argv, cmd), 0);
	}
	if (check_builtins(cmd) == 1 && cmd->nbr == 1)
		return (one_cmd_and_builtin(cmd, s, argv), 0);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		error_cmd(argv, cmd, 1);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (check_builtins(cmd) == 0)
		{
			if (dup2(cmd->fd.read, 0) == -1 || dup2(cmd->fd.write, 1) == -1)
				error_cmd(argv, cmd, 126);
			close_fd_child(cmd);
		}
		exec_cmd(cmd, s, argv);
	}
	else
		close_fd_parent(cmd);
	return (1);
}

void	pipe_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s)
{
	//proteger ?
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	if (cmd->index_pid != cmd->nbr - 1 && pipe(cmd->fd.pipe) == -1)
		error_cmd(argv, cmd, 1);
	while (cmd->index_pid < cmd->nbr)
	{
		convert_list(cmd, argv);
		cmd->fd.previous = cmd->fd.pipe[0];
		if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
			if (pipe(cmd->fd.pipe) == -1)
				error_cmd(argv, cmd, 1);
		}
		if (setup_cmd(argv, cmd, s) == -1)
			return ;
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
