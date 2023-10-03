/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main _pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/10/01 20:47:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main_pipex(t_lst_cmd *cmd, char **env)
{
	t_pipex	pipex_cmd;
	int		status;

	pipex_cmd.envp = env;
	//pipex_cmd.argv = av;
	if (init_struct(&pipex_cmd, cmd) == 0)
		return (0);
	pipex_cmd.pid = malloc(sizeof(pid_t) * pipex_cmd.max);
	if (!pipex_cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	pipex(cmd, &pipex_cmd);
	pipex_cmd.index_pid--;
	while (pipex_cmd.index_pid > 0)
	{
		waitpid(pipex_cmd.pid[pipex_cmd.index_pid - 1], &status, 0);
		pipex_cmd.index_pid--;
	}
	free(pipex_cmd.pid);
	return (0);
}
