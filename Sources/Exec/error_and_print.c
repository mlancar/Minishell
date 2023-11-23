/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:59:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error_access_cmd(t_struct_data *s, t_cmd *cmd)
{
	if (cmd->name[0] == NULL)
		error_cmd(s, cmd, 127);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fd_parent(cmd);
	g_exit = 127;
}

void	error_access_slash(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	close_fd_parent(cmd);
	if (errno == EACCES)
		g_exit = 126;
	else
		g_exit = 127;
}

void	error_open_file(t_cmd *cmd, char *infile, char *outfile)
{
	ft_putstr_fd("minishell: ", 2);
	if (infile)
		ft_putstr_fd(infile, 2);
	else if (outfile)
		ft_putstr_fd(outfile, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	close_all_fd(cmd);
}

void	print_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	error_dir(t_cmd *cmd, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Is a directory", 2);
	ft_putstr_fd("\n", 2);
	cmd->pid[cmd->index] = -1;
	g_exit = exit_code;
}
