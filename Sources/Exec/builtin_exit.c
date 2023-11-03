/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:50:22 by malancar          #+#    #+#             */
/*   Updated: 2023/11/03 18:28:24 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"


// Note: It is also to taken into consideration that an exit code
// with a value greater than 255 returns an exit code modulo 256.
// For Example: If we execute a statement exit(9999)
// then it will execute exit(15) as 9999%256 = 15.

int		builtin_exit(t_cmd *cmd)
{
	int	return_value;

	(void)cmd;
	return_value = 0;
	free(cmd->argv);
	free(cmd->env);
	free(cmd->path);
	free(cmd->pid);
	if (cmd->nbr != 1)
	{
		check_close(cmd, cmd->fd.pipe[0]);
		check_close(cmd, cmd->fd.pipe[1]);
	}
	check_close(cmd, cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd, cmd->fd.read);
	else
		check_close(cmd, cmd->fd.tmp);
	// if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
	// 	check_close(cmd, cmd->fd.other_pipe);
	exit(return_value);
}
