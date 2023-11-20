/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:56 by malancar          #+#    #+#             */
/*   Updated: 2023/11/20 15:12:29 by malancar         ###   ########.fr       */
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
	while (cmd->name[nbr_arg])
		nbr_arg++;
	return (nbr_arg);
}

void	error_builtins(t_cmd *cmd)
{
	if (cmd->name[2])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name[0], 2);
		ft_putstr_fd(": too many arguments", 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->name[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd->name[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

int	ft_atol(char *str, long *n)
{
	int	i;
	int	sign;
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
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && result <= LONG_MAX)
	{
		//printf("str[i] = %c\n", str[i]);
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if ((sign == -1 && result >= ((unsigned long)LONG_MAX + 1))
		|| (sign == 1 && result > LONG_MAX))
		return (0);
	*n = result * sign;
	return (1);
}