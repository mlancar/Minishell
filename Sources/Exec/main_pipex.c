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
#include "minishell.h"

int	main_pipex(t_lst_cmd *argv, char **env, t_lst_env **env_list)
{
	t_cmd	cmd;
	int		status;

	cmd.env = env;
	(void)env_list;
	init_struct(&cmd, argv);
	cmd.pid = malloc(sizeof(pid_t) * cmd.nbr);
	if (!cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	pipex(argv, &cmd, env_list);
	while (cmd.index_pid >= 0)
	{
		waitpid(cmd.pid[cmd.index_pid], &status, 0);
		cmd.index_pid--;
	}
	free(cmd.pid);
	return (0);
}
