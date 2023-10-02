/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/10/01 20:18:46 by malancar         ###   ########.fr       */
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

void	free_and_exit(char *str, t_pipex *pipex_cmd)
{
	free_tab(pipex_cmd->name);
	free(pipex_cmd->path);
	free(pipex_cmd->pid);
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_access_pipex_cmd(t_pipex *pipex_cmd)
{
	ft_putstr_fd(pipex_cmd->name[pipex_cmd->index], 2);
	write(2, ": command not found\n", 20);
	error_pipex_cmd(127, pipex_cmd);
}

void	error_pipex_cmd(int return_value, t_pipex *pipex_cmd)
{
	printf("error exec\n");
	free_tab(pipex_cmd->name);
	free(pipex_cmd->path);
	free(pipex_cmd->pid);
	check_close(pipex_cmd->fd[0]);
	check_close(pipex_cmd->fd[1]);
	check_close(pipex_cmd->outfile);
	if (pipex_cmd->if_here_doc == 0)
		check_close(pipex_cmd->infile);
	else
		check_close(pipex_cmd->fd_tmp);
	if ((pipex_cmd->index_pid != pipex_cmd->first) && (pipex_cmd->index_pid != pipex_cmd->last))
		check_close(pipex_cmd->previous_fd);
	exit(return_value);
}

void	error_empty_string(t_pipex *pipex_cmd)
{
	ft_putstr_fd(pipex_cmd->argv[pipex_cmd->index], 2);
	write(2, ": command not found\n", 20);
	free(pipex_cmd->pid);
	check_close(pipex_cmd->fd[0]);
	check_close(pipex_cmd->fd[1]);
	check_close(pipex_cmd->outfile);
	if (pipex_cmd->if_here_doc == 0)
		check_close(pipex_cmd->infile);
	else
		check_close(pipex_cmd->fd_tmp);
	if ((pipex_cmd->index_pid != pipex_cmd->first) && (pipex_cmd->index_pid != pipex_cmd->last))
		check_close(pipex_cmd->previous_fd);
	exit(127);
}
