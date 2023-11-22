/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/11/22 21:08:16 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_cmd_directory(t_cmd *cmd)
{
	DIR	*directory;

	directory = opendir(cmd->name[0]);
	if (directory)
	{
		closedir(directory);
		error_dir(cmd, 126);
		return (-1);
	}
	return (0);
}

int	is_cmd_empty(t_cmd *cmd)
{
	if (cmd->name[0] == NULL)
	{
		cmd->pid[cmd->index_pid] = -1;
		return (-1);
	}
	else if (cmd->name[0][0] == '\0')
		return (0);
	return (1);
}

int	is_command_valid(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	int		path_line;
	char	*path;
	int		return_value;

	return_value = is_cmd_empty(cmd);
	if (return_value == -1)
		return (-1);
	else if (return_value == 0)
		return (0);
	if (is_cmd_directory(cmd) == -1)
		return (-1);
	if (check_builtins(cmd) == 1)
		return (1);
	path_line = get_env_line(cmd, "PATH=");
	path = &cmd->env[path_line][5];
	if (path_line == 0)
		path = NULL;
	if (check_access(cmd_list, cmd, path) == 0)
		return (0);
	return (1);
}
