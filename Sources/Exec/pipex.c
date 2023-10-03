/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/10/03 17:16:15 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	dup_fd(t_pipex *pipex_cmd, int fd_in, int fd_out, int fd_other)
{
	//d'abord dup pipe et apres dup redir si y'en a !
	//printf("path[%s], argv[%s], argv[%s]\n", pipex_cmd->path, pipex_cmd->name[0], pipex_cmd->name[1]);
	if (pipex_cmd->max == 1)
	{
		if (dup2(fd_in, 0) != -1)//pas besoin de dup uen cmd, si pas pipe et pas redir !
			close(fd_other);
	}
	else if (pipex_cmd->index_pid == pipex_cmd->first)
	{
		if ((dup2(fd_out, 1) != -1) || (dup2(fd_in, 0) != -1))
			close(fd_other);
	}
	else if  (pipex_cmd->index_pid == pipex_cmd->last)
	{
		if (dup2(fd_in, 1) != -1)
			return ;//close ? je sais pas ?
	}
	else if ((pipex_cmd->index_pid != pipex_cmd->first)
			&& (pipex_cmd->index_pid != pipex_cmd->last))
	{
		if ((dup2(fd_out, 1) != -1) || (dup2(fd_other, 0) != -1))
			close(fd_other);
	}
}

void	exec_cmd(t_lst_cmd *cmd, int fd_in, int fd_out, int fd_other, t_pipex *pipex_cmd)
{
	if (pipex_cmd->index_pid == pipex_cmd->first)
		fd_in = 0;
	//printf("cmd = %d\n", pipex_cmd->index);
	//dprintf(2, "fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
	//printf("fd[0] = %d, fd[1] = %d\n", pipex_cmd->fd[0], pipex_cmd->fd[1]);
	pipex_cmd->pid[pipex_cmd->index_pid - 1] = fork();
	if (pipex_cmd->pid[pipex_cmd->index_pid - 1] < 0)
		free_and_exit("fork", pipex_cmd);
	else if (pipex_cmd->pid[pipex_cmd->index_pid - 1] == 0)
	{
		if (check_command(cmd, pipex_cmd) == 0)
			error_access_cmd(pipex_cmd);
		dup_fd(pipex_cmd, fd_in, fd_out, fd_other);
		//dprintf(2, "ici fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
		if (execve(pipex_cmd->path, pipex_cmd->argv, pipex_cmd->envp))
			error_cmd(0, pipex_cmd);
		// else
		// 	error_pipex_cmd(0, pipex_cmd);
	}
	else
	{
		if (pipex_cmd->max == 1)
		{
			//printf("cc\n");
		}
		else if (pipex_cmd->index_pid == pipex_cmd->first)
		{
			check_close(fd_out);
			check_close(fd_other);
		}
		else
		{
			//check_close(fd_in);
			check_close(fd_other);
		}
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
	
	if (pipe(pipex_cmd->fd) == -1)
		free_and_exit("pipe", pipex_cmd);
	//printf("pipex_cmd->index_pid = %d, cmd->max = %d\n", pipex_cmd->index_pid, pipex_cmd->max);
	//printf("fd[0] = %d, fd[1] = %d\n", pipex_cmd->fd[0], pipex_cmd->fd[1]);
	while (pipex_cmd->index_pid <= pipex_cmd->max)
	{
		pipex_cmd->argv = convert(cmd);
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
		if (cmd != NULL)
			cmd = cmd->next;
	}
}
