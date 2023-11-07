/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 18:02:36 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	free_and_exit(t_cmd *cmd, int exit_code)
{
	free(cmd->argv);
	free(cmd->env);
	free(cmd->path);
	free(cmd->pid);
	exit(exit_code);
}

void	error_access_cmd(t_lst_cmd *argv, t_cmd *cmd)
{
	if (cmd->argv[0] == NULL)
		error_cmd(argv, cmd, 127);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	print_error( t_lst_cmd *argv, t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (argv->file)
		ft_putstr_fd(argv->file->infile, 2);
	else
		ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	error_cmd(t_lst_cmd *argv, t_cmd *cmd, int exit_code)
{
	print_error(argv, cmd);
	check_close(cmd, cmd->fd.pipe[0]);
	check_close(cmd, cmd->fd.pipe[1]);
	check_close(cmd, cmd->fd.write);
	if (cmd->if_here_doc == 0)
		check_close(cmd, cmd->fd.read);
	else
		check_close(cmd, cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd, cmd->fd.other_pipe);
	free_and_exit(cmd, exit_code);
}
