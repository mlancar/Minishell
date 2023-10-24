/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/10/24 15:39:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//REDIRECTION :
//ls <in <<stop<in2<<stop>out<<onstopcettefois!
//ouvrir dnas l'ordre les infile outfile et cas d'echec quitter
//en cas de reussite utiliser les derniers infile outfile dans l'ordre
//pas fork si une cmd et builtin
//open tous les heredocs en meme temps

void redirection(t_lst_cmd *argv, t_cmd *cmd)
{
	while (argv->file)
	{
		set_redirections(argv, cmd);
		if (cmd->if_here_doc == 1)
		{
			here_doc(argv->file->limiter, cmd);
			check_close(cmd->fd.read);
			cmd->fd.read = cmd->fd.tmp;
			//printf("fd tmp = %d\n", cmd->fd.tmp);
			unlink(cmd->files.rand_name);
		}
		argv->file = argv->file->next;
	}
}

void	fork_and_exec_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s)
{
	set_fd(cmd);
	redirection(argv, cmd);
	cmd->pid[cmd->index_pid] = fork();
	if (cmd->pid[cmd->index_pid] < 0)
		free_and_exit("fork", cmd);
	if (cmd->pid[cmd->index_pid] == 0)
	{
		if (dup2(cmd->fd.read, 0) == -1) 
			error_cmd(0, cmd);
		if (cmd->nbr != 0 && dup2(cmd->fd.write, 1) == -1)
			error_cmd(0, cmd);
		if (check_command(argv, cmd, s) == 0)
			error_access_cmd(cmd);
		close_fd_child(argv, cmd);
		if (execve(cmd->path, cmd->argv, cmd->env))
			error_cmd(0, cmd);
	}
	else
		close_fd_parent(argv, cmd);
}

void	pipe_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s)
{
	if (cmd->index_pid != cmd->nbr - 1 && pipe(cmd->fd.pipe) == -1)
		free_and_exit("pipe", cmd);
	while (cmd->index_pid < cmd->nbr)
	{
		cmd->argv = convert_list(argv);
		cmd->fd.previous = cmd->fd.pipe[0];
		if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
		if (pipe(cmd->fd.pipe) == -1)
			free_and_exit("pipe", cmd);
		}
		fork_and_exec_cmd(argv, cmd, s);
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
