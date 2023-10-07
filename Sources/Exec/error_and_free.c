/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/10/07 16:08:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_and_exit(char *str, t_cmd *cmd)
{
	free_tab(cmd->name);
	free(cmd->path);
	free(cmd->pid);
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_access_cmd(t_cmd *cmd)
{
	ft_putstr_fd(cmd->name[cmd->index], 2);
	write(2, ": command not found\n", 20);
	error_cmd(127, cmd);
}

void	error_cmd(int return_value, t_cmd *cmd)
{
	printf("error\n");
	free_tab(cmd->name);
	free(cmd->path);
	free(cmd->pid);
	check_close(cmd->fd.pipe[0]);
	check_close(cmd->fd.pipe[1]);
	check_close(cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd->fd.read);
	else
		check_close(cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd->fd.close);
	exit(return_value);
}

void	error_empty_string(t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[cmd->index], 2);
	write(2, ": command not found\n", 20);
	free(cmd->pid);
	check_close(cmd->fd.pipe[0]);
	check_close(cmd->fd.pipe[1]);
	check_close(cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd->fd.read);
	else
		check_close(cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd->fd.close);
	exit(127);
}
