/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:40 by malancar          #+#    #+#             */
/*   Updated: 2023/10/04 20:04:02 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main_pipex(t_lst_cmd *argv, char **env)
{
	t_pipex	cmd;
	int		status;

	cmd.envp = env;
	//cmd.argv = av;
	if (init_struct(&cmd, argv) == 0)
		return (0);
	//printf("cmd max = %d\n", cmd.max);
	cmd.pid = malloc(sizeof(pid_t) * cmd.max);
	if (!cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	//printf("cmdpid = %p\n", &cmd.pid);
	dprintf(2, "%p\n", argv->info);
	pipex(argv, &cmd);
	//cmd.index_pid--;
	while (cmd.index_pid > 0)
	{
		//printf("index = %d\n", cmd.index_pid);
		waitpid(cmd.pid[cmd.index_pid - 1], &status, 0);
		cmd.index_pid--;
	}
	free(cmd.pid);
	return (0);
}
