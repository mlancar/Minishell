/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:28:37 by malancar          #+#    #+#             */
/*   Updated: 2023/10/03 16:04:49 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

int	check_slash_and_access(t_lst_cmd *cmd, t_pipex *pipex_cmd)
{
	if (ft_strchr(cmd->arg->name, '/'))
	{
		//printf("cc slash\n");
		pipex_cmd->path = ft_strdup(*(pipex_cmd->name));
		if (access(pipex_cmd->path, X_OK) == 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	check_command(t_lst_cmd *cmd, t_pipex *pipex_cmd)
{
	int		i;
	int		find_path;
	char	*path;

	i = 0;
	find_path = 0;
	// if (pipex_cmd->argv[pipex_cmd->index][0] == '\0')
	// 	error_empty_string(pipex_cmd);
	//pipex_cmd->name = ft_split
	// while (pipex_cmd->name[i])
	// {
	// 	printf("%s\n", pipex_cmd->name[i]);
	// 	i++;
	// }
	// if (!pipex_cmd->name || (!pipex_cmd->name[0]))
	// 	return (0);
	while (pipex_cmd->envp[i])
	{
		if (pipex_cmd->envp[i][0] == 'P' && pipex_cmd->envp[i][1] == 'A' &&
			pipex_cmd->envp[i][2] == 'T' && pipex_cmd->envp[i][3] == 'H' &&
			pipex_cmd->envp[i][4] == '=')
			find_path = i;
		i++;
	}
	path = &pipex_cmd->envp[find_path][5];
	if (find_path == 0)
		path = NULL;
	if (check_access(cmd, pipex_cmd, path) == 0)
		return (0);
	
	return (1);
}

int	check_access_with_path(t_pipex *pipex_cmd, char ***split_path)
{
	if (access(pipex_cmd->path, X_OK) == 0)
	{
		free_tab(*split_path);
		return (1);
	}
	return (0);
}

int	check_access(t_lst_cmd *cmd, t_pipex *pipex_cmd, char *path)
{
	char	**split_path;
	int		i;

	i = 0;
	if (check_slash_and_access(cmd, pipex_cmd) > 0)
		return (1);
	else if (check_slash_and_access(cmd, pipex_cmd) < 0)
		return (0);
	split_path = ft_split(path, ':');
	while (split_path && split_path[i])
	{
		pipex_cmd->path = ft_strjoin(split_path[i], cmd->arg->name, '/');
		if (check_access_with_path(pipex_cmd, &split_path))
			return (1);
		free(pipex_cmd->path);
		i++;
	}
	if (split_path)
		free_tab(split_path);
	pipex_cmd->path = ft_strdup(cmd->arg->name);
	if (access(pipex_cmd->path, X_OK) == 0)
		return (1);
	return (0);
}
