/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:45 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 14:02:01 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	builtins_env(t_cmd *cmd, t_lst_env *env_list)
{
	if (cmd->argv[1])
		return (0);
	while (env_list)
	{
		ft_putstr_fd(env_list->line, cmd->fd.write);
		ft_putstr_fd("\n", cmd->fd.write);
		env_list = env_list->next;
	}
	return (1);
}
