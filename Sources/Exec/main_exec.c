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
	free(cmd->path);

}

int	start_exec(t_lst_cmd *argv, t_struct_data *s)
{
	t_cmd	cmd;
	int		status;


	convert_list_env(&cmd, s);
	init_struct(&cmd, argv);
	cmd.pid = malloc(sizeof(pid_t) * cmd.nbr);
	if (!cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	loop_exec(argv, &cmd, s);
	//
	if (check_builtins(&cmd) == 1 && cmd.nbr == 1)
	{
		free(cmd.pid);
		free(cmd.env);
		free(cmd.argv);
		free(cmd.fd_hd);
		return (0);
	}
	cmd.index_pid--;
	//printf("pid = %d, cmdnbr = %d\n", cmd.pid[cmd.index_pid], cmd.nbr);
	if (cmd.pid[cmd.index_pid] != -1)
	{
		while (cmd.index_pid >= 0)
		{
			// printf("cc wait\n");
			// printf("pid = %d\n", cmd.pid[cmd.index_pid]);
			waitpid(cmd.pid[cmd.index_pid], &status, 0);
			//printf("cc wait 2\n");
			cmd.index_pid--;
		}
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);

	}
	int i = 0;
	while (i < cmd.nbr)
	{
		//printf("fd_hd = %d\n", cmd.fd_hd[i]);
		check_close(&cmd, cmd.fd_hd[i]);
		i++;
	}
	free(cmd.pid);
	free(cmd.fd_hd);
	free(cmd.env);
	free(cmd.argv);
	return (0);
}
