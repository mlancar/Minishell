/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:17:08 by malancar          #+#    #+#             */
/*   Updated: 2023/10/08 11:55:25 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

//pas besoin de dup uen cmd, si pas pipe et pas redir !
//d'abord dup pipe et apres dup redir si y'en a !
	
void	dup_fd(t_cmd *cmd, int fd_in, int fd_out, int fd_other)
{
	if (cmd->nbr == 1)
	{
		if (dup2(fd_in, 0) != -1)
		{
			check_close(fd_other);
			check_close(fd_out);
		}
	}
	else if (cmd->index_pid == cmd->first)
	{
		if ((dup2(fd_out, 1) != -1) || (dup2(fd_in, 0) != -1))
		{
			check_close(fd_out);
			check_close(fd_other);
		}
	}
	else if  (cmd->index_pid == cmd->last)
	{
		if (dup2(fd_in, 1) != -1)
		{
			check_close(fd_in);
			check_close(fd_other);
			
		}
	}
	else if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
	{
		if ((dup2(fd_out, 1) != -1) || (dup2(fd_other, 0) != -1))
		{
			check_close(fd_out);
			check_close(fd_other);
		}
	}
}

void	exec_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other)
{
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	else if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_command(argv, cmd) == 0)
			error_access_cmd(cmd);
		dup_fd(cmd, fd_in, fd_out, fd_other);
		//dprintf(2, "ici fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
		if (execve(cmd->path, cmd->argv, cmd->envp))
			error_cmd(0, cmd);
		// else
		// 	error_cmd(0, cmd);
	}
	else
	{
		if (cmd->nbr == 1)
		{
			check_close(fd_out);
			check_close(fd_other);
		}
		else if (cmd->index_pid == cmd->first)
			check_close(fd_other);
		else if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
			check_close(fd_out);
			check_close(fd_other);
		}
		else if (cmd->index_pid == cmd->last)
		{
			check_close(fd_in);
			check_close(fd_other);
		}
	}
}

void	first_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	if (cmd->if_here_doc == 1)
	{
		here_doc(cmd->argv[2], cmd);
		exec_cmd(argv, cmd, cmd->fd_tmp, cmd->fd[1], cmd->fd[0]);
		unlink(cmd->rand_name);
	}
	else
		exec_cmd(argv, cmd, cmd->files->in, cmd->fd[1], cmd->fd[0]);
}

void	pipex(t_lst_argv *argv, t_cmd *cmd)
{
	
	if (pipe(cmd->fd) == -1)
		free_and_exit("pipe", cmd);
	//printf("cmd->index_pid = %d, cmd->nbr = %d\n", cmd->index_pid, cmd->nbr);
	//printf("fd[0] = %d, fd[1] = %d\n", cmd->fd[0], cmd->fd[1]);
	while (cmd->index_pid < cmd->nbr)
	{
		//printf("index pid = %d, first cmd = %d, last cmd = %d\n", cmd->index_pid, cmd->first, cmd->last);
		//dprintf(2, "%p\n", argv->info);
		cmd->argv = convert(argv);
		//dprintf(2, "%p\n", argv->info);
		if (cmd->index_pid == cmd->first)
			first_cmd(argv, cmd);
		else if (cmd->index_pid == cmd->last)
			exec_cmd(argv, cmd, cmd->fd[0], cmd->files->out, cmd->fd[1]);
		else if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
			//printf("MIDDLE\n");
			cmd->previous_fd = cmd->fd[0];
			if (pipe(cmd->fd) == -1)
				free_and_exit("pipe", cmd);
			exec_cmd(argv, cmd, cmd->previous_fd, cmd->fd[1], cmd->fd[0]);
		}
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
