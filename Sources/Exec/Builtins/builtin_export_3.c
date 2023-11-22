/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:36 by auferran          #+#    #+#             */
/*   Updated: 2023/11/22 15:45:12 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	error_arg_export(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->name[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(cmd->name[1], 2);
	ft_putstr_fd("': not a valid identifer\n", 2);
	g_exit = 1;
}

void	print_export(t_cmd *cmd, t_lst_env *lst_export)
{
	while (lst_export)
	{
		ft_putstr_fd(lst_export->line, cmd->fd.write);
		ft_putstr_fd("\n", cmd->fd.write);
		lst_export = lst_export->next;
	}
}

int	its_valid(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '=')
	{
		g_exit = 1;
		error_arg_export(cmd);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
		{
			g_exit = 1;
			error_arg_export(cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
