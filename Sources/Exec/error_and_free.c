/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:28:45 by malancar          #+#    #+#             */
/*   Updated: 2023/11/20 17:07:23 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	free_parsing(s);
	g_exit = exit_code;
	exit(g_exit);
}

void	error_access_cmd(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (cmd->name[0] == NULL)
		error_cmd(s, cmd_list, cmd, 127);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fd_parent(cmd);
	g_exit = 127;
}

void	print_error( t_lst_cmd *cmd_list, t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd_list->file)
	{
		if (cmd_list->file->infile)
			ft_putstr_fd(cmd_list->file->infile, 2);
		else if (cmd_list->file->outfile)
			ft_putstr_fd(cmd_list->file->outfile, 2);
	}
	else
		ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	error_cmd(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd, int exit_code)
{
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
	free_and_exit(s, cmd, exit_code);
}
