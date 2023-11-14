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

int	main_exec(t_lst_cmd *argv, t_struct_env *s)
{
	t_cmd	cmd;
	int		status; 


	convert_list_env(&cmd, s);
	init_struct(&cmd, argv);
	cmd.pid = malloc(sizeof(pid_t) * cmd.nbr);
	if (!cmd.pid)
		return (write(1, "pid error\n", 10), 0);
	pipe_cmd(argv, &cmd, s);

	if (check_builtins(&cmd) == 1 && cmd.nbr == 1)
	{
		free(cmd.pid);
		//remplacer par fonction qui  free tout
		free(cmd.env);
		free(cmd.argv);
		return (0);
	}
	
	cmd.index_pid--;
	while (cmd.index_pid >= 0)
	{
		waitpid(cmd.pid[cmd.index_pid], &status, 0);
		cmd.index_pid--;
	}
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = 128 + WTERMSIG(status);
	free(cmd.pid);
	free(cmd.env); 
	return (0);
}
