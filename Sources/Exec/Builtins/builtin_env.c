/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:18 by auferran          #+#    #+#             */
/*   Updated: 2023/11/20 15:12:29 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	builtin_env(t_cmd *cmd, t_lst_env *env_list)
{
	if (cmd->name[1])
	{
		if (its_option(cmd->name))
			return (error("minishell: env: invalid option\n"), 1);
		return (error("minishell: env: invalid argument\n"), 1);
	}
	while (env_list)
	{
		ft_putstr_fd(env_list->line, cmd->fd.write);
		ft_putstr_fd("\n", cmd->fd.write);
		env_list = env_list->next;
	}
	return (1);
}
