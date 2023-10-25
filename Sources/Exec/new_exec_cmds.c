/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/10/25 17:49:48 by malancar         ###   ########.fr       */
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
			unlink(cmd->files.rand_name);
		}
		argv->file = argv->file->next;
	}
}

void	one_cmd_and_builtin(t_cmd *cmd, t_struct_env *s)
{
	(void)s;
	if (dup2(cmd->fd.read, 0) == -1) 
		error_cmd(0, cmd);
	if (cmd->nbr != 0 && dup2(cmd->fd.write, 1) == -1)
		error_cmd(0, cmd);
	if (exec_builtins(cmd, s) == 0)
		error_cmd(0, cmd);
}

void	exec_cmd(t_cmd *cmd, t_struct_env *s)
{
		if (check_builtins(cmd) == 1)
		{
			if (exec_builtins(cmd, s) == 0)
				error_cmd(0, cmd);
		}
		else
		{
			if (execve(cmd->path, cmd->argv, cmd->env))
				error_cmd(0, cmd);
		}
}
//changer nom:
void	fork_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s)
{
	set_fd(cmd);
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
		if (dup2(cmd->fd.read, 0) == -1) 
			error_cmd(0, cmd);
		if (cmd->nbr != 0 && dup2(cmd->fd.write, 1) == -1)
			error_cmd(0, cmd);	
		close_fd_child(argv, cmd);
		exec_cmd(cmd, s);
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
		//printf("ici : cmd->argv = %s, cmd->index_pid = %d\n", cmd->argv[0], cmd->index_pid);
		cmd->fd.previous = cmd->fd.pipe[0];
		if ((cmd->index_pid != cmd->first)
			&& (cmd->index_pid != cmd->last))
		{
		if (pipe(cmd->fd.pipe) == -1)
			free_and_exit("pipe", cmd);
		}
		fork_cmd(argv, cmd, s);
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
