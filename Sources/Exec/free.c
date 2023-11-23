/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:01:25 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 20:39:04 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_exec(t_cmd *cmd)
{
	free(cmd->pid);
	free(cmd->name);
	free(cmd->env);
	free(cmd->fd_hd);
}

void	free_and_set(t_cmd *cmd, char **array)
{
	if (cmd->name[0])
	{
		if (*array)
		{
			free(*array);
			*array = NULL;
		}
	}
	
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_and_exit(t_struct_data *s, t_cmd *cmd, int exit_code)
{
	free_exec(cmd);
	if (cmd->path)
		free(cmd->path);
	free_parsing(s);
	g_exit = exit_code;
	exit(g_exit);
}

void	free_and_close_hd(t_struct_data *s, t_cmd *cmd)
{
	free(cmd->fd_hd);
	free(cmd->pid);
	free(cmd->env);
	free(cmd->path);
	free(cmd->name);
	free_parsing(s);
	check_close(cmd, &cmd->fd.write);
	check_close(cmd, &cmd->fd.tmp);
	exit(EXIT_SUCCESS);
}
