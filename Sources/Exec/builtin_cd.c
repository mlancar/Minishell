/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:53:30 by malancar          #+#    #+#             */
/*   Updated: 2023/11/03 17:48:34 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

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

void		error_cd(t_cmd *cmd)
{
	if (cmd->argv[2])
		printf("%s: too many arguments\n", cmd->argv[0]);
	else
		printf("%s: %s: %s\n", cmd->argv[0], cmd->argv[1], strerror(errno));
	
}

int	builtin_cd(t_cmd *cmd)
{
	char	*path;
	int		i;
	int		len;

	len = 0;
	i = 0;
	path = cmd->argv[1];
	while (cmd->argv[len])
		len++;
	if (len > 2)
		return (error_cd(cmd), 0);
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
	if (chdir(path) == -1)
		return (error_cd(cmd), 0);
	return (1);
}
