/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:39 by malancar          #+#    #+#             */
/*   Updated: 2023/10/30 12:01:40 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

void	print_export(t_cmd *cmd, t_lst_env *lst_export)
{
	while (lst_export)
	{
		ft_putstr_fd(lst_export->line, cmd->fd.write);
		ft_putstr_fd("\n", cmd->fd.write);
		lst_export = lst_export->next;
	}
}

int	its_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
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
