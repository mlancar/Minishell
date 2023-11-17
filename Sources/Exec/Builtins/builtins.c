/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:21 by malancar          #+#    #+#             */
/*   Updated: 2023/11/13 18:05:04 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	check_builtins(t_cmd *cmd)
{
	if (!cmd->argv)
		return (0);
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "env"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "unset"))
		return (1);
	else
		return (0);
}

int	exec_builtins(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv)
{
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "echo"))
		g_exit = builtin_echo(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "pwd"))
		g_exit = builtin_pwd(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export"))
		g_exit = builtin_export(cmd, s);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "env"))
		g_exit = builtin_env(cmd, s->lst_env);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "cd"))
		g_exit = builtin_cd(cmd);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "exit"))
		g_exit = builtin_exit(argv, cmd, s);
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "unset"))
		g_exit = builtin_unset(cmd, s);
	else
		return (0);
	return (1);
}
