/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:55:46 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:52:30 by malancar         ###   ########.fr       */
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
		error_access_slash(cmd);
		return (-1);
	}
	return (0);
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

int	check_access(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd, char *path)
{
	char	**split_path;
	int		i;

	i = check_slash_and_access(cmd_list, cmd);
	if (i == 1)
		return (1);
	else if (i == -1)
		return (0);
	split_path = ft_split(path, ':');
	i = 0;
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
	error_access_cmd(s, cmd);
	return (0);
}
