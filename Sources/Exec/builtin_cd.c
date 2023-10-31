/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:53:30 by malancar          #+#    #+#             */
/*   Updated: 2023/10/31 18:05:09 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

void	error_cd(t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	error_cmd(127, cmd);
}

int	get_home_path(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		//printf("env[i] = %s\n", cmd->env[i]);
		if (ft_strncmp("HOME=", cmd->env[i], 4) == 0)
		{
			//printf("la i = %d\n", i);
			return (i);
		}
		//printf("i = %d\n", i);
		i++;
	}
	return (0);
}

int	builtin_cd(t_cmd *cmd)
{
	DIR		*dir;
	char	*path;
	int		i;

	i = 0;
	dir = 0;
	path = cmd->argv[1];
	if (path == NULL)
	{
		i = get_home_path(cmd);
		//printf("%d\n",get_home_path(cmd));
		if (i == 0)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": HOME not set\n", 2);
			return (0);
		}
		path = &cmd->env[i][5];
		//printf("home_path = %s\n", path);
		
	}
	//printf("%s %s\n", cmd->argv[0], cmd->argv[1]);
	dir = opendir(path);
	//printf("%p\n", dir);
	if (!dir)
	{
		error_cd(cmd);
	}
	//printf("cc\n");
	chdir(path);
	return (1);
}
