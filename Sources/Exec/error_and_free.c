/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 20:29:26 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error_access_cmd(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (cmd->name[0] == NULL)
		error_cmd(s, cmd_list, cmd, 127);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fd_parent(cmd);
	g_exit = 127;
}

void	error_open_file(t_cmd *cmd, char *infile, char *outfile)
{
	int	i;

	i = 0;
	ft_putstr_fd("minishell: ", 2);
	if (infile)
		ft_putstr_fd(infile, 2);
	else if (outfile)
		ft_putstr_fd(outfile, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (cmd->nbr > 0)
	{
		check_close(cmd, &cmd->fd.pipe[0]);
		check_close(cmd, &cmd->fd.pipe[1]);
	}
	check_close(cmd, &cmd->fd.write);
	if (cmd->heredoc == 0)
		check_close(cmd, &cmd->fd.read);
	else
		check_close(cmd, &cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd, &cmd->fd.other_pipe);
	while (i < cmd->nbr)
	{
		check_close(cmd, &cmd->fd_hd[i]);
		i++;
	}
}

void	print_error(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	(void)cmd_list;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	error_exec(t_struct_data *s, t_cmd *cmd, int exit_code)
{
	if (cmd->nbr > 0)
	{
		check_close(cmd, &cmd->fd.pipe[0]);
		check_close(cmd, &cmd->fd.pipe[1]);
	}
	check_close(cmd, &cmd->fd.write);
	if (cmd->heredoc == 0)
		check_close(cmd, &cmd->fd.read);
	else
		check_close(cmd, &cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd, &cmd->fd.other_pipe);
	if (cmd->path)
		free(cmd->path);
	free_and_exit(s, cmd, exit_code);
}

void	error_dir(t_cmd *cmd, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Is a directory", 2);
	ft_putstr_fd("\n", 2);
	cmd->pid[cmd->index_pid] = -1;
	g_exit = exit_code;
}

void	error_cmd(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd,
	int exit_code)
{
	int	i;

	i = 0;
	if (cmd->name[0])
		print_error(cmd_list, cmd);
	if (cmd->nbr > 0)
	{
		check_close(cmd, &cmd->fd.pipe[0]);
		check_close(cmd, &cmd->fd.pipe[1]);
	}
	check_close(cmd, &cmd->fd.write);
	if (cmd->heredoc == 0)
		check_close(cmd, &cmd->fd.read);
	else
		check_close(cmd, &cmd->fd.tmp);
	if ((cmd->index_pid != cmd->first) && (cmd->index_pid != cmd->last))
		check_close(cmd, &cmd->fd.other_pipe);
	while (i < cmd->nbr)
	{
		check_close(cmd, &cmd->fd_hd[i]);
		i++;
	}
	free_and_exit(s, cmd, exit_code);
}
