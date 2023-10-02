/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/10/02 17:27:23 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	dup_fd_and_exec(t_pipex *pipex_cmd, int fd_in, int fd_out, int fd_other)
{
	//int i = 0;
	// while (pipex_cmd->argv[i])
	// {
	// 	dprintf(2, "%s\n", pipex_cmd->argv[i]);
	// 	i++;
	// }
	// i = 0;
	// while (pipex_cmd->name[i])
	// {
	// 	printf("%s\n", pipex_cmd->argv[i]);
	// 	i++;
	// }
	//printf("path[%s], argv[%s], argv[%s]\n", pipex_cmd->path, pipex_cmd->name[0], pipex_cmd->name[1]);
	if (pipex_cmd->index_pid == pipex_cmd->first)
	{
		if (dup2(fd_out, 0) != -1)
		{
			close(fd_other);
			if (execve(pipex_cmd->path, pipex_cmd->argv, pipex_cmd->envp))
				error_pipex_cmd(0, pipex_cmd);
		}
	}
	else if  (pipex_cmd->index_pid == pipex_cmd->last)
	{
		//printf("cc\n");
		if (dup2(fd_in, 1) != -1)
		{
			if (execve(pipex_cmd->path, pipex_cmd->argv, pipex_cmd->envp))
				error_pipex_cmd(0, pipex_cmd);
		}
	}
}

void	exec_cmd(t_lst_cmd *cmd, int fd_in, int fd_out, int fd_other, t_pipex *pipex_cmd)
{
	if (pipex_cmd->index_pid == pipex_cmd->first)
		fd_in = 0;
	//printf("cmd = %d\n", pipex_cmd->index);
	// printf("fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
	// printf("fd[0] = %d, fd[1] = %d\n", pipex_cmd->fd[0], pipex_cmd->fd[1]);
	pipex_cmd->pid[pipex_cmd->index_pid - 1] = fork();
	if (pipex_cmd->pid[pipex_cmd->index_pid - 1] < 0)
		free_and_exit("fork", pipex_cmd);
	else if (pipex_cmd->pid[pipex_cmd->index_pid - 1] == 0)
	{
		if (check_command(cmd, pipex_cmd) == 0)
			error_access_pipex_cmd(pipex_cmd);
		dup_fd_and_exec(pipex_cmd, fd_in, fd_out, fd_other);
		// else
		// 	error_pipex_cmd(0, pipex_cmd);
	}
	else
	{
		//check_close(fd_in);
		check_close(fd_out);
	}
}

void	first_pipex_cmd(t_lst_cmd *cmd, t_pipex *pipex_cmd)
{
	if (pipex_cmd->if_here_doc == 1)
	{
		here_doc(pipex_cmd->argv[2], pipex_cmd);
		exec_cmd(cmd, pipex_cmd->fd_tmp, pipex_cmd->fd[1], pipex_cmd->fd[0], pipex_cmd);
		unlink(pipex_cmd->rand_name);
	}
	else
		exec_cmd(cmd, pipex_cmd->infile, pipex_cmd->fd[1], pipex_cmd->fd[0], pipex_cmd);
}

void	pipex(t_lst_cmd *cmd, t_pipex *pipex_cmd)
{
	pipex_cmd->argv = convert(cmd);
	if (pipe(pipex_cmd->fd) == -1)
		free_and_exit("pipe", pipex_cmd);
	//printf("cmd->max = %d\n", pipex_cmd->max);
	// if (pipe() == -1)
	// 	free_and_exit("pipe", pipex_cmd);
	//printf("fd[0] = %d, fd[1] = %d\n", pipex_cmd->fd[0], pipex_cmd->fd[1]);
	while (pipex_cmd->index_pid <= pipex_cmd->max)
	{
		if (pipex_cmd->index_pid == pipex_cmd->first)
			first_pipex_cmd(cmd, pipex_cmd);
		else if (pipex_cmd->index_pid == pipex_cmd->last)
			exec_cmd(cmd, pipex_cmd->fd[0], pipex_cmd->outfile, pipex_cmd->fd[1], pipex_cmd);
		else if ((pipex_cmd->index_pid != pipex_cmd->first)
			&& (pipex_cmd->index_pid != pipex_cmd->last))
		{
			pipex_cmd->previous_fd = pipex_cmd->fd[0];
			if (pipe(pipex_cmd->fd) == -1)
				free_and_exit("pipe", pipex_cmd);
			exec_cmd(cmd, pipex_cmd->previous_fd, pipex_cmd->fd[1], pipex_cmd->fd[0], pipex_cmd);
		}
		pipex_cmd->index++;
		pipex_cmd->index_pid++;
		
	}
}
