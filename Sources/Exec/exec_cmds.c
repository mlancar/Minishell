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

void	last_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	printf("\nlast cmd : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if ((dup2(cmd->fd.read, 0) != -1) && (dup2(cmd->fd.write, 1) != -1))
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(cmd->fd.read);
			check_close(cmd->fd.close);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	else
	{
		check_close(cmd->fd.read);
		check_close(cmd->fd.close);
		
	}
}

void	middle_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	printf("\nmiddle cmd : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
		if (cmd->pid[cmd->index_pid] == 0)
	{
		if ((dup2(cmd->fd.read, 0) != -1) && (dup2(cmd->fd.write, 1) != -1))
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(cmd->fd.write);
			check_close(cmd->fd.read);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	else
	{
		check_close(cmd->fd.write);
		check_close(cmd->fd.read);
	}
}

void	first_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	printf("\nfirst cmd : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if ((dup2(cmd->fd.read, 0) != -1) && (dup2(cmd->fd.write, 1) != -1))
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			check_close(cmd->fd.close);
			check_close(cmd->fd.write);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
	else
	{
		check_close(cmd->fd.close);
		check_close(cmd->fd.write);
	}
}

void	one_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	printf("\n one cmd : read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (check_command(argv, cmd) == 0)
			error_access_cmd(cmd);
		if (dup2(cmd->fd.read, 0) != -1)
		{
			if (check_command(argv, cmd) == 0)
				error_access_cmd(cmd);
			if (execve(cmd->path, cmd->argv, cmd->envp))
				error_cmd(0, cmd);
		}
		else
			error_cmd(0, cmd);
	}
}

void	exec_cmds(t_lst_argv *argv, t_cmd *cmd)
{
	//printf("index pid = %d, cmd nbr = %d\n", cmd->index_pid, cmd->nbr - 1);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	if (cmd->index_pid == cmd->first)
		first_cmd(argv, cmd);
	else if (cmd->index_pid == cmd->last)
		last_cmd(argv, cmd);
	else if ((cmd->index_pid != cmd->first)
		&& (cmd->index_pid != cmd->last))
	{
		if (pipe(cmd->fd.pipe) == -1)
			free_and_exit("pipe", cmd);
		middle_cmd(argv, cmd);
	}
}

void	exec_one_cmd(t_lst_argv *argv, t_cmd *cmd)
{
	cmd->argv = convert_list(argv);
	cmd->fd.read = 0;
	cmd->fd.write = 1;
	cmd->fd.close = -1;
	set_files(argv, cmd);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	one_cmd(argv, cmd);
}

void	pipex(t_lst_argv *argv, t_cmd *cmd)
{
	if (cmd->index_pid == cmd->nbr - 1)
		exec_one_cmd(argv, cmd);
	else
	{
		if (pipe(cmd->fd.pipe) == -1)
			free_and_exit("pipe", cmd);
		while (cmd->index_pid < cmd->nbr)
		{
			cmd->argv = convert_list(argv);
			set_fd(cmd);
			set_files(argv, cmd);
			exec_cmds(argv, cmd);
			cmd->index++;
			cmd->index_pid++;
			if (argv != NULL)
				argv = argv->next;
		}
	}
}

//printf("name = %s\n", cmd->name[0]);
// if (cmd->if_here_doc == 1)
// {
// 	here_doc(cmd->argv[2], cmd);
// 	exec_argv(argv, cmd->fd_tmp, cmd->fd[1], cmd->fd[0], cmd);
// 	unlink(cmd->rand_name);
// }
