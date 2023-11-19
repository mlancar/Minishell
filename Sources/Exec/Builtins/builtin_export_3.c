/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:36 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 17:20:37 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
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
		return (error("minishell: export: invalid argument\n"), 0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
			return (error("minishell: export: invalid argument\n"), 0);
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
