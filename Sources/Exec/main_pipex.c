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

#include "pipex.h"

int	main_pipex(t_lst_argv *argv, char **env)
{
	t_cmd	cmd;
	int		status;

	cmd.envp = env;
	init_struct(&cmd, argv);
	cmd.pid = malloc(sizeof(pid_t) * cmd.nbr);
	if (!cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	pipex(argv, &cmd);
	while (cmd.index_pid >= 0)
	{
		waitpid(cmd.pid[cmd.index_pid], &status, 0);
		cmd.index_pid--;
	}
	free(cmd.pid);
	return (0);
}
