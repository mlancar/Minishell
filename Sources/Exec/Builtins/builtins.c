/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:21 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 22:36:07 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	check_builtins(t_cmd *cmd)
{
	if (!cmd->name)
		return (0);
	if (cmd->name[0] && !ft_strcmp(cmd->name[0], "echo"))
		return (1);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "pwd"))
		return (1);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "export"))
		return (1);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "env"))
		return (1);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "cd"))
		return (1);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "exit"))
		return (1);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "unset"))
		return (1);
	else
		return (0);
}

int	exec_builtins(t_cmd *cmd, t_struct_data *s)
{
	if (cmd->name[0] && !ft_strcmp(cmd->name[0], "echo"))
		builtin_echo(cmd);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "pwd"))
		builtin_pwd(cmd);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "export"))
		builtin_export(cmd, s);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "env"))
		builtin_env(cmd, s->lst_env);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "cd"))
		builtin_cd(cmd, s);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "exit"))
		builtin_exit(cmd, s);
	else if (cmd->name[0] && !ft_strcmp(cmd->name[0], "unset"))
		builtin_unset(cmd, s);
	else
		return (0);
	return (1);
}
