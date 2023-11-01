/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/11/01 17:09:38 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	//printf("tab = %s\n", tab[0]);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_and_exit(char *str, t_cmd *cmd)
{
	//dprintf(2, "free and exit\n");
	free_tab(cmd->argv);
	free(cmd->path);
	free(cmd->pid);
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_access_cmd(t_cmd *cmd)
{
	//dprintf(2, "error access\n");
	if (cmd->argv[0] == NULL)
		error_cmd(127, cmd);
	ft_putstr_fd(cmd->argv[0], 2);
	write(2, ": no such file or directory\n", 29);
	error_cmd(127, cmd);
}

void	error_cmd(int return_value, t_cmd *cmd)
{
	//dprintf(2, "error\n");
	free_tab(cmd->argv);
	free(cmd->path);
	free(cmd->pid);
	check_close(cmd, cmd->fd.pipe[0]);
	check_close(cmd, cmd->fd.pipe[1]);
	check_close(cmd, cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd, cmd->fd.read);
	else
		check_close(cmd, cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd, cmd->fd.other_pipe);
	exit(return_value);
}

void	error_empty_string(t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[cmd->index], 2);
	write(2, ": command not found\n", 20);
	free(cmd->pid);
	check_close(cmd, cmd->fd.pipe[0]);
	check_close(cmd, cmd->fd.pipe[1]);
	check_close(cmd, cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd, cmd->fd.read);
	else
		check_close(cmd, cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd, cmd->fd.other_pipe);
	exit(127);
}
