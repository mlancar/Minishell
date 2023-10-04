/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/10/04 17:04:22 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	check_slash_and_access(t_lst_cmd *argv, t_pipex *cmd)
{
	//printf("argv->info->name %p %s\n", &argv->info->name, argv->info->name);
	if (ft_strchr(argv->info->name, '/'))
	{
		//printf("cc slash\n");
		cmd->path = ft_strdup(argv->info->name);
		if (access(cmd->path, X_OK) == 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	check_command(t_lst_cmd *argv, t_pipex *cmd)
{
	int		i;
	int		find_path;
	char	*path;

	i = 0;
	find_path = 0;
	
	if (argv->info->name[0] == '\0')
		error_empty_string(cmd);
	//cmd->name = ft_split
	// while (cmd->name[i])
	// {
	// 	printf("%s\n", cmd->name[i]);
	// 	i++;
	// }
	// if (!cmd->name || (!cmd->name[0]))
	// 	return (0);
	while (cmd->envp[i])
	{
		if (cmd->envp[i][0] == 'P' && cmd->envp[i][1] == 'A' &&
			cmd->envp[i][2] == 'T' && cmd->envp[i][3] == 'H' &&
			cmd->envp[i][4] == '=')
			find_path = i;
		i++;
	}
	path = &cmd->envp[find_path][5];
	if (find_path == 0)
		path = NULL;
	if (check_access(argv, cmd, path) == 0)
		return (0);
	
	return (1);
}

int	check_access_with_path(t_pipex *cmd, char ***split_path)
{
	if (access(cmd->path, X_OK) == 0)
	{
		free_tab(*split_path);
		return (1);
	}
	return (0);
}

int	check_access(t_lst_cmd *argv, t_pipex *cmd, char *path)
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
		cmd->path = ft_strjoin(split_path[i], argv->info->name, '/');
		if (check_access_with_path(cmd, &split_path))
			return (1);
		free(cmd->path);
		i++;
	}
	if (split_path)
		free_tab(split_path);
	cmd->path = ft_strdup(argv->info->name);
	if (access(cmd->path, X_OK) == 0)
		return (1);
	return (0);
}
