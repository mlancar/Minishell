/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/11/18 22:40:45 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	exec_child(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv)
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

void	exec_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s)
{
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		error_cmd(argv, cmd, 1);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (check_builtins(cmd) == 0)
		{
			printf("cmd = %s fdread = %d, fdwrite = %d\n", cmd->argv[0], cmd->fd.read, cmd->fd.write);
			if (dup2(cmd->fd.read, 0) == -1 || dup2(cmd->fd.write, 1) == -1)
			{
				error_cmd(argv, cmd, 126);
			}
			close_fd_child(cmd);
			check_close(cmd, cmd->fd.tmp);
			close(cmd->fd.tmp);
		}
		exec_child(cmd, s, argv);
	}
	else
		close_fd_parent(cmd);
}

int	setup_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s)
{	
	init_fd(cmd);
	if (redirection_one_cmd(argv, cmd) == 0)
		return (0);
	
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
	return (1);
}

void	loop_exec(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_redirections(argv, cmd, s) == -1)
	{
		cmd->pid[cmd->index_pid] = -1;
		return ;
	}
	if (cmd->nbr != 1 && pipe(cmd->fd.pipe) == -1)
		error_cmd(argv, cmd, 1);
	while (cmd->index_pid < cmd->nbr)
	{
		convert_list(cmd, argv);
		if (cmd->nbr != 1)
			cmd->fd.previous = cmd->fd.pipe[0];
		if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
			if (pipe(cmd->fd.pipe) == -1)
				error_cmd(argv, cmd, 1);
		}
		
		if (setup_cmd(argv, cmd, s) == -1)
			return ;
		exec_cmd(argv, cmd, s);
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
