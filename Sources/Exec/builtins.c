/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:21 by malancar          #+#    #+#             */
/*   Updated: 2023/10/31 14:33:11 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

int	check_builtins(t_cmd *cmd)
{
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "pwd"))
	{
		//printf("cc pwd\n");
		return (1);
	}
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "env"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	else
		return (0);
}

int	exec_builtins(t_cmd *cmd, t_struct_env *s)
{
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "echo"))
		g_exit = builtins_echo(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "pwd"))
		g_exit = builtins_pwd(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export"))
		g_exit = builtins_export(cmd, s);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "env"))
		g_exit = builtins_env(cmd, s->lst_env);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "cd"))
		g_exit = builtin_cd(cmd);
	else
		return (0);
	return (1);
}
