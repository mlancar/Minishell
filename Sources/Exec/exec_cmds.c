/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/10/05 14:38:55 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other)
{
	dprintf(2, "last cmd : fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
	(void)fd_out;
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_command(argv, cmd) == 0)
			error_access_cmd(cmd);	
		if (dup2(fd_in, 1) != -1)
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(fd_in);
			check_close(fd_other);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
	}
	else
	{
		check_close(fd_in);
		check_close(fd_other);
		
	}
}

void	middle_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other)
{

	(void)fd_in;
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if ((dup2(fd_out, 1) != -1) || (dup2(fd_other, 0) != -1))
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(fd_out);
			check_close(fd_other);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
	}
	else
	{
		check_close(fd_out);
		check_close(fd_other);
	}
}

void	first_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other)
{
	dprintf(2, "first cmd : fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_command(argv, cmd) == 0)
			error_access_cmd(cmd);
		if ((dup2(fd_out, 1) != -1) || (dup2(fd_in, 0) != -1))
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(fd_other);
			check_close(fd_out);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
	}	
	else
	{
		check_close(fd_other);
		check_close(fd_out);
	}
}

void	one_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other)
{
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_command(argv, cmd) == 0)
			error_access_cmd(cmd);
		if (dup2(fd_in, 0) != -1)
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(fd_other);
			check_close(fd_out);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
		{
			check_close(fd_out);
			check_close(fd_other);
		}
	}
}

void	exec_cmds(t_lst_argv *argv, t_cmd *cmd)
{
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	if (cmd->index_pid == cmd->nbr - 1)
		one_cmd(argv, cmd, cmd->files.in, cmd->fd[1], cmd->fd[0]);
	if (cmd->index_pid == cmd->first)
		first_cmd(argv, cmd, cmd->files.in, cmd->fd[1], cmd->fd[0]);
	else if (cmd->index_pid == cmd->last)
		last_cmd(argv, cmd, cmd->fd[0], cmd->files.out, cmd->fd[1]);
	else if ((cmd->index_pid != cmd->first)
		&& (cmd->index_pid != cmd->last))
	{
		cmd->previous_fd = cmd->fd[0];
		if (pipe(cmd->fd) == -1)
			free_and_exit("pipe", cmd);
		middle_cmd(argv, cmd, cmd->previous_fd, cmd->fd[1], cmd->fd[0]);
	}
}

void	pipex(t_lst_argv *argv, t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index_pid < cmd->nbr)
	{
		cmd->argv = convert_list(argv);
		init_files(argv, cmd);
		exec_cmds(argv, cmd);
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}

//printf("name = %s\n", cmd->name[0]);
// if (cmd->if_here_doc == 1)
// {
// 	here_doc(cmd->argv[2], cmd);
// 	exec_argv(argv, cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
// 	unlink(cmd->rand_name);
// }
