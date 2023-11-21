/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:53:05 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 21:55:46 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_child(t_cmd *cmd, t_struct_data *s, t_lst_cmd *cmd_list)
{
	if (check_builtins(cmd) == 1)
	{
		if (exec_builtins(cmd, s) == 0)
			error_cmd(s, cmd_list, cmd, 126);
		close_fd_child(cmd);
		free_exec(cmd);
		free_parsing(s);
		g_exit = 0;
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (execve(cmd->path, cmd->name, cmd->env))
			error_exec(s, cmd, 126);
	}
}

void	signal_exec(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		
	}
}

void	exec_cmd(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s)
{
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		error_cmd(s, cmd_list, cmd, 1);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		//signal(SIGINT, signal_exec);
		if (check_builtins(cmd) == 0)
		{
			//dprintf(2, "%s read = %d, write = %d pipe = %d\n", cmd->name[0], cmd->fd.read, cmd->fd.write, cmd->fd.other_pipe);
			//leak quand dup2 fail
			if (dup2(cmd->fd.read, 0) == -1 || dup2(cmd->fd.write, 1) == -1)
				error_cmd(s, cmd_list, cmd, 126);
			close_fd_child(cmd);
			check_close(cmd, &cmd->fd.tmp);
			check_close(cmd, &cmd->fd.tmp);
		}
		exec_child(cmd, s, cmd_list);
	}
	else
		close_fd_parent(cmd);
}

int	setup_exec(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd)
{
	int	check_cmd;
	
	init_fd(cmd);
	if (redirection_one_cmd(s, cmd_list, cmd) == 0)
	{
		close_fd_parent(cmd);
		cmd->pid[cmd->index_pid] = -1;
		return (0);
	}
	check_cmd = check_command(cmd_list, cmd);
	if (check_cmd == -1)
	{
		close_fd_parent(cmd);
		return (0);
	}
	else if (check_cmd == 0)
	{
		cmd->pid[cmd->index_pid] = -1;
		error_access_cmd(s, cmd_list, cmd);
		return (0);
	}
	return (1);
}

void	loop_exec(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s)
{
	int	setup;
	
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_redirections(cmd_list, cmd, s) == 0)
		return ;
	if (cmd->nbr != 1 && pipe(cmd->fd.pipe) == -1)
		error_cmd(s, cmd_list, cmd, 1);
	while (cmd->index_pid < cmd->nbr)
	{
		convert_list(cmd, cmd_list);
		pipe_cmd(s, cmd, cmd_list);
		setup = setup_exec(s, cmd_list, cmd);
		if (setup == 1)
		{
			if (check_builtins(cmd) == 1 && cmd->nbr == 1)
				return (one_cmd_builtin(cmd, s, cmd_list));
			else
				exec_cmd(cmd_list, cmd, s);
		}
		else if (setup == -1)
			return ;
		cmd->index++;
		cmd->index_pid++;
		if (check_builtins(cmd) == 0)
		{
			free(cmd->path);
			cmd->path = NULL;
		}
		if (cmd_list != NULL)
			cmd_list = cmd_list->next;
	}
}

int	start_exec(t_lst_cmd *cmd_list, t_struct_data *s)
{
	t_cmd	cmd;

	convert_list_env(&cmd, s);
	init_struct(&cmd, cmd_list);
	loop_exec(cmd_list, &cmd, s);
	if (check_builtins(&cmd) == 1 && cmd.nbr == 1)
	{
		free_exec(&cmd);
		return (0);
	}
	wait_cmd(&cmd);
	close_fd_hd(&cmd);
	free_exec(&cmd);
	return (0);
}