/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/10/24 17:33:11 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_slash_and_access(t_lst_cmd *argv, t_cmd *cmd)
{
	//printf("argv->arg->name %p %s\n", &argv->arg->name, argv->arg->name);
	if (ft_strchr(argv->arg->name, '/'))
	{
		//printf("cc slash\n");
		cmd->path = ft_strdup(argv->arg->name);
		if (access(cmd->path, X_OK) == 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	check_command(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s)
{
	int		i;
	int		find_path;
	char	*path;

	i = 0;
	find_path = 0;
	if (exec_builtins(cmd, s) == 1)
	{
		
	}
	while (cmd->env[i])
	{
		if (cmd->env[i][0] == 'P' && cmd->env[i][1] == 'A' &&
			cmd->env[i][2] == 'T' && cmd->env[i][3] == 'H' &&
			cmd->env[i][4] == '=')
			find_path = i;
		i++;
	}
	path = &cmd->env[find_path][5];
	if (find_path == 0)
		path = NULL;
	if (check_access(argv, cmd, path) == 0)
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

int	check_access(t_lst_cmd *argv, t_cmd *cmd, char *path)
{
	char	**split_path;
	int		i;

	i = 0;
	if (check_slash_and_access(argv, cmd) > 0)
		return (1);
	else if (check_slash_and_access(argv, cmd) < 0)
		return (0);
	split_path = ft_split(path, ':');
	while (split_path && split_path[i])
	{
		cmd->path = ft_strjoin(split_path[i], argv->arg->name, '/');
		if (check_access_with_path(cmd, &split_path))
			return (1);
		free(cmd->path);
		i++;
	}
	if (split_path)
		free_tab(split_path);
	cmd->path = ft_strdup(argv->arg->name);
	if (access(cmd->path, X_OK) == 0)
		return (1);
	return (0);
}
