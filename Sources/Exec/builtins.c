/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:21 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 18:33:01 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int		builtin_arg_nbr(t_cmd *cmd)
{
	int	nbr_arg;
	
	nbr_arg = 0;
	while (cmd->argv[nbr_arg])
		nbr_arg++;
	if (nbr_arg > 2)
		return (-1);
	else
		return (1);
}

void		error_builtins(t_cmd *cmd)
{
	if (cmd->argv[2])
	{
		ft_putstr_fd("minihsell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": too many arguments", 2);
		ft_putstr_fd("\n", 2);
		//printf("minishell: %s: too many arguments\n", cmd->argv[0]);
	}
	else
	{
		ft_putstr_fd("minihsell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		//printf("%s: %s: %s\n", cmd->argv[0], cmd->argv[1], strerror(errno));
	}
	
}

int	check_builtins(t_cmd *cmd)
{
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
	else
		return (0);
}

int	exec_builtins(t_cmd *cmd, t_struct_env *s, t_lst_cmd *argv)
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
	else if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "exit"))
		g_exit = builtin_exit(argv, cmd);
	else
		return (0);
	return (1);
}
