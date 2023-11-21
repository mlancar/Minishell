/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 22:02:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_slash_and_access(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	if (ft_strchr(cmd_list->arg->name, '/'))
	{
		cmd->path = ft_strdup(cmd_list->arg->name);
		if (access(cmd->path, X_OK) == 0)
			return (1);
	}
	
	return (0);
}

int	check_command(t_lst_cmd *cmd_list, t_cmd *cmd)
{
	int		path_line;
	char	*path;
	DIR		*dir;

	//printf("cmd = %s\n", cmd->name[0]);
	if (cmd->name[0] == NULL)
	{
		cmd->pid[cmd->index_pid] = -1;
		return (-1);
	}
	else if (cmd->name[0][0] == '\0')
		return(0);
	dir = opendir(cmd->name[0]);
	if (dir)
	{
		closedir(dir);
		error_dir(cmd, 126);
		return (-1);
	}
	else if (check_builtins(cmd) == 1)
		return (1);
	path_line = get_env_line(cmd, "PATH=");
	path = &cmd->env[path_line][5];
	if (path_line == 0)
		path = NULL;
	if (check_access(cmd_list, cmd, path) == 0)
		return (0);
	return (1);
}

int	check_access_with_path(t_cmd *cmd, char ***split_path)
{
	if (access(cmd->path, X_OK) == 0)
	{
		free_tab(*split_path);
		return (1);
	}
	return (0);
}

int	check_access(t_lst_cmd *cmd_list, t_cmd *cmd, char *path)
{
	char	**split_path;
	int		i;

	i = 0;
	if (check_slash_and_access(cmd_list, cmd) == 1)
		return (1);
	split_path = ft_split(path, ':');
	while (split_path && split_path[i])
	{
		cmd->path = ft_strjoin(split_path[i], cmd_list->arg->name, '/');
		if (check_access_with_path(cmd, &split_path))
			return (1);
		free(cmd->path);
		i++;
	}
	if (split_path)
		free_tab(split_path);
	cmd->path = ft_strdup(cmd_list->arg->name);
	if (access(cmd->path, X_OK) == 0)
		return (1);
	return (0);
}
