/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:56 by malancar          #+#    #+#             */
/*   Updated: 2023/11/08 17:21:05 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_env_line(t_cmd *cmd, char *str)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strncmp(str, cmd->env[i], 4) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	builtin_arg_nbr(t_cmd *cmd)
{
	int	nbr_arg;

	nbr_arg = 0;
	while (cmd->argv[nbr_arg])
		nbr_arg++;
	return (nbr_arg);
}

void	error_builtins(t_cmd *cmd)
{
	if (cmd->argv[2])
	{
		ft_putstr_fd("minihsell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": too many arguments", 2);
		ft_putstr_fd("\n", 2);
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
	}
}
