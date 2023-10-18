/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/10/18 15:49:38 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//REDIRECTION :
//ls <in <<stop<in2<<stop>out<<onstopcettefois!
//ouvrir dnas l'ordre les infile outfile et cas d'echec quitter
//en cas de reussite utiliser les derniers infile outfile dans l'ordre
//pas fork si une cmd et builtin
//open tous les heredocs en meme temps

// void	one_cmd(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
// {
// 	//printf("\n one cmd : fd.tmp = %d, read = %d, write = %d, close = %d\n", cmd->fd.tmp, cmd->fd.read, cmd->fd.write, cmd->fd.close);
// 	if (cmd->pid[cmd->index_pid] == 0)
// 	{
// 		if (dup2(cmd->fd.read, 0) != -1)
// 		{
// 			// if (argv->file->outfile && cmd->fd.write, 1) != -1)
// 			// {
				
// 			// }
// 			if (check_command(argv, cmd, env_list) == 0)
// 				error_access_cmd(cmd);
// 			check_close(cmd->fd.read);
// 			if (execve(cmd->path, cmd->argv, cmd->env))
// 				error_cmd(0, cmd);
// 		}
// 		else
// 			error_cmd(0, cmd);
// 	}
// 	check_close(cmd->fd.read);
// 	check_close(cmd->fd.write);
// }

// void	exec_one_cmd(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
// {
// 	cmd->argv = convert_list(argv);
// 	cmd->fd.read = 0;
// 	cmd->fd.write = 1;
// 	cmd->fd.close = -1;
// 	while (argv->file)
// 	{
// 		set_redirections(argv, cmd);
// 		if (cmd->if_here_doc == 1)
// 		{
// 			here_doc(argv->file->limiter, cmd);
// 			cmd->fd.read = cmd->fd.tmp;
// 			unlink(cmd->files.rand_name);
// 		}

// 		argv->file = argv->file->next;
// 	}
// 	cmd->pid[cmd->index_pid] = fork();
// 	if (cmd->pid[cmd->index_pid] < 0)
// 		free_and_exit("fork", cmd);
// 	one_cmd(argv, cmd, env_list);
// }
// 	//printf("read = %d, write = %d, close = %d\n", cmd->fd.read, cmd->fd.write, cmd->fd.close);

void redirection(t_lst_cmd *argv, t_cmd *cmd)
{
	while (argv->file)
	{
		set_redirections(argv, cmd);
		if (cmd->if_here_doc == 1)
		{
			here_doc(argv->file->limiter, cmd);
			cmd->fd.read = cmd->fd.tmp;
			printf("fd tmp = %d\n", cmd->fd.tmp);
			//check_close(cmd->fd.tmp);
			unlink(cmd->files.rand_name);
		}
		argv->file = argv->file->next;
	}
}

void	new_exec_cmds(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
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
		if (check_command(argv, cmd, env_list) == 0)
			error_access_cmd(cmd);
		close_fd_child(argv, cmd);
		if (execve(cmd->path, cmd->argv, cmd->env))
			error_cmd(0, cmd);
	}
	else
		close_fd_parent(argv, cmd);
}

void	pipex(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list)
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
		new_exec_cmds(argv, cmd, env_list);
		cmd->index++;
		cmd->index_pid++;
		if (argv != NULL)
			argv = argv->next;
	}
}
