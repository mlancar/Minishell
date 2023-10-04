/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:27:53 by malancar          #+#    #+#             */
/*   Updated: 2023/10/04 19:58:41 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"

// //d'abord dup pipe et apres dup redir si y'en a !

// void	last_cmd(t_lst_cmd *argv, t_pipex *cmd, int fd_in, int fd_out, int fd_other)
// {
// 	//(void)fd_out;
// 	(void)fd_other;
// 	//printf("last cmd : %d[%d]\n", cmd->pid[cmd->index_pid - 1], cmd->index_pid - 1);
// 	cmd->pid[cmd->index_pid] = fork();
// 	if (cmd->pid[cmd->index_pid] < 0)
// 		free_and_exit("fork", cmd);
// 	else if (cmd->pid[cmd->index_pid - 1] == 0)
// 	{
// 		if (check_command(argv, cmd) == 0)
// 			error_access_cmd(cmd);
// 		if (dup2(fd_in, 1) != -1)
// 		{
// 			check_close(fd_out);
// 			if (execve(cmd->path, cmd->argv, cmd->envp))
// 				error_cmd(0, cmd);
// 		}
// 		//check_close(fd_out);
// 	}
// 	else
// 	{
// 		check_close(fd_out);
// 		//check_close(fd_in);
		
// 	}
// }

// void	middle_cmd(t_lst_cmd *argv, t_pipex *cmd, int fd_in, int fd_out, int fd_other)
// {
// 	(void)fd_in;
// 	cmd->previous_fd = cmd->fd[0];
// 	if (pipe(cmd->fd) == -1)
// 		free_and_exit("pipe", cmd);
// 	//printf("middle cmd : %d[%d]\n", cmd->pid[cmd->index_pid - 1], cmd->index_pid - 1);
// 	if (cmd->pid[cmd->index_pid] < 0)
// 		free_and_exit("fork", cmd);
// 	else if (cmd->pid[cmd->index_pid] == 0)
// 	{
// 		if (check_command(argv, cmd) == 0)
// 			error_access_cmd(cmd);
// 		else if ((cmd->index_pid != cmd->first)
// 			&& (cmd->index_pid != cmd->last))
// 		{
// 			if ((dup2(fd_out, 1) != -1) || (dup2(fd_other, 0) != -1))
// 			{
// 				close(fd_other);
// 				if (execve(cmd->path, cmd->argv, cmd->envp))
// 				error_cmd(0, cmd);
// 			}
// 		}
		
// 	}
// 	else
// 	{
// 		check_close(fd_other);
// 	}
// }

// void	first_cmd(t_lst_cmd *argv, t_pipex *cmd, int fd_in, int fd_out, int fd_other)
// {
// 	fd_in = 0;
// 	//dprintf(2, "fd_in = %d, fd_out = %d, fd_other = %d\n", fd_in, fd_out, fd_other);
// 	//printf("first cmd : %d[%d]\n", cmd->pid[cmd->index_pid - 1], cmd->index_pid - 1);
// 	//printf("%d[%d]", cmd->pid[cmd->index_pid], cmd->index_pid);
// 	cmd->pid[cmd->index_pid] = fork();
// 	if (cmd->pid[cmd->index_pid] < 0)
// 		free_and_exit("fork", cmd);
// 	else if (cmd->pid[cmd->index_pid] == 0)
// 	{
// 		if (check_command(argv, cmd) == 0)
// 			error_access_cmd(cmd);
// 		if (cmd->max == 1)
// 		{
// 			if (dup2(fd_in, 0) != -1)
// 			{
// 				check_close(fd_other);
// 				check_close(fd_out);
// 				if (execve(cmd->path, cmd->argv, cmd->envp))
// 					error_cmd(0, cmd);
// 			}	
// 		}
// 		else
// 		{
// 			if ((dup2(fd_out, 1) != -1) || (dup2(fd_in, 0) != -1))
// 			{
// 				check_close(fd_other);
// 				if (execve(cmd->path, cmd->argv, cmd->envp))
// 					error_cmd(0, cmd);
// 			}
					
// 		}
// 	}	
// 	else
// 	{
// 		check_close(fd_out);
// 		check_close(fd_other);
// 	}
// }

// void	pipex(t_lst_cmd *argv, t_pipex *cmd)
// {

// 	if (pipe(cmd->fd) == -1)
// 		free_and_exit("pipe", cmd);
// 	//printf("fd[0] = %d, fd[1] = %d\n", cmd->fd[0], cmd->fd[1]);
// 	while (cmd->index_pid < cmd->max)
// 	{
// 		cmd->argv = convert(argv);
// 		//printf("name = %s\n", cmd->name[0]);
// 		// if (cmd->if_here_doc == 1)
// 		// {
// 		// 	here_doc(cmd->argv[2], cmd);
// 		// 	exec_cmd(cmd, cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
// 		// 	unlink(cmd->rand_name);
// 		// }
// 		if (cmd->index_pid == cmd->first)
// 			first_cmd(argv, cmd, cmd->infile, cmd->fd[1], cmd->fd[0]);
// 		else if (cmd->index_pid == cmd->last)
// 			last_cmd(argv, cmd, cmd->fd[0], cmd->outfile, cmd->fd[1]);
// 		else if ((cmd->index_pid != cmd->first)
// 			&& (cmd->index_pid != cmd->last))
// 		{
// 			middle_cmd(argv, cmd, cmd->previous_fd, cmd->fd[1], cmd->fd[0]);
// 		}
// 		cmd->index++;
// 		cmd->index_pid++;
// 		if (argv != NULL)
// 			argv = argv->next;
// 	}
// }
