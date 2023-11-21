/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/10/05 14:38:55 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	free_exec(t_cmd *cmd)
{
	free(cmd->pid);
	free(cmd->name);
	free(cmd->env);
	free(cmd->fd_hd);
}

void	wait_cmd(t_cmd *cmd)
{
	int		status;
	int		i;

	//printf("pid = %d, indexpid = %d\n", cmd->pid[cmd->index_pid], cmd->index_pid);
	i = 0;
	cmd->index_pid--;
	//printf("pid = %d, indexpid = %d\n", cmd->pid[cmd->index_pid], cmd->index_pid);
	
	while (i <= cmd->index_pid)
	{
		if (cmd->pid[i] != -1)
		{
			waitpid(cmd->pid[i], &status, 0);
		}
		//printf("status = %d\n", status);
		i++;
		
	}
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = 128 + WTERMSIG(status);
}
