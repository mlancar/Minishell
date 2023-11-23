/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:53:39 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:59:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	wait_cmd(t_cmd *cmd)
{
	int		status;
	int		i;

	i = 0;
	cmd->index--;
	while (i <= cmd->index)
	{
		if (cmd->pid[i] != -1)
		{
			waitpid(cmd->pid[i], &status, 0);
			if (WIFEXITED(status))
				g_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					ft_putstr("\n");
				else if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", 2);
			}
		}
		i++;
	}
}
