/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 18:03:29 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	one_cmd_builtin(t_cmd *cmd, t_struct_data *s, t_lst_cmd *cmd_list)
{
	if (exec_builtins(cmd, s) == 0)
		error_cmd(s, cmd_list, cmd, 126);
	close_fd_parent(cmd);
}

void	pipe_cmd(t_struct_data *s, t_cmd *cmd, t_lst_cmd *cmd_list)
{
	if (cmd->nbr != 1)
		cmd->fd.previous = cmd->fd.pipe[0];
	if ((cmd->index_pid != cmd->first)
		&& (cmd->index_pid != cmd->last))
	{
		if (pipe(cmd->fd.pipe) == -1)
			error_cmd(s, cmd_list, cmd, 1);
	}
}
