/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/10/30 16:32:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void redirection(t_lst_cmd *argv, t_cmd *cmd)
{
	while (argv->file)
	{
		set_redirections(argv, cmd);
		if (cmd->if_here_doc == 1)
		{
			here_doc(argv->file->limiter, cmd);
			//dprintf(2, "fd tmp heredoc = %d\n", cmd->fd.tmp);
			check_close(cmd, cmd->fd.read);
			cmd->fd.read = cmd->fd.tmp;
			//dprintf(2, "fd read heredoc = %d\n", cmd->fd.read);
			unlink(cmd->files.rand_name);
		}
		argv->file = argv->file->next;
	}
}

void	one_cmd_and_builtin(t_cmd *cmd, t_struct_env *s)
{
	(void)s;
	if (exec_builtins(cmd, s) == 0)
		error_cmd(0, cmd);
	close_fd_parent(cmd);
	return ;
}

void	exec_cmd(t_cmd *cmd, t_struct_env *s)
{
		if (check_builtins(cmd) == 1)
		{
			if (exec_builtins(cmd, s) == 0)
				error_cmd(0, cmd);
			//printf("close fd builtin\n");
			close_fd(cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (execve(cmd->path, cmd->argv, cmd->env))
				error_cmd(0, cmd);
		}
}

void	setup_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s)
{
	init_fd(cmd);
	redirection(argv, cmd);
	if (check_command(argv, cmd) == 0)
		error_access_cmd(cmd);
	if (check_builtins(cmd) == 1 && cmd->nbr == 1)
		return (one_cmd_and_builtin(cmd, s));
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_builtins(cmd) == 0)
		{
			//printf("cmd = %s cc pas builtin\n", cmd->argv[0]);
			if (dup2(cmd->fd.read, 0) == -1 || dup2(cmd->fd.write, 1) == -1) 
				error_cmd(0, cmd);
			close_fd_child(cmd);
		}
		exec_cmd(cmd, s);
	}
	else
		close_fd_parent(cmd);
}

void	pipe_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s)
{
	if (cmd->index_pid != cmd->nbr - 1 && pipe(cmd->fd.pipe) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index_pid < cmd->nbr)
	{
		cmd->argv = convert_list(argv);
		//printf("ici : cmd->argv = %s, cmd->index_pid = %d\n", cmd->argv[0], cmd->index_pid);
		cmd->fd.previous = cmd->fd.pipe[0];
		if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
		if (pipe(cmd->fd.pipe) == -1)
			free_and_exit("pipe", cmd);
		}
		setup_cmd(argv, cmd, s);
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
