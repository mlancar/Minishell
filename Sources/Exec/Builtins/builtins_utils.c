/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:56 by malancar          #+#    #+#             */
/*   Updated: 2023/11/09 17:21:19 by malancar         ###   ########.fr       */
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

unsigned long	ft_atol(char *str)
{
	int	i;
	unsigned long	sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		//printf("str[i] = %c\n", str[i]);
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	//protect unsigned long
	return (result * sign);
}
