/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:02 by auferran          #+#    #+#             */
/*   Updated: 2023/11/20 15:12:29 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	its_option_echo(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	option;
	int	arg;

	i = 1;
	option = 0;
	arg = 0;
	while (cmd->name[i])
	{
		if (its_option_echo(cmd->name[i]) && arg == 0)
			option = 1;
		else if (cmd->name[i])
		{
			arg = 1;
			ft_putstr_fd(cmd->name[i], cmd->fd.write);
			if (cmd->name[i + 1])
				ft_putstr_fd(" ", cmd->fd.write);
		}
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", cmd->fd.write);
	return (1);
}
