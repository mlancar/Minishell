/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_env_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:00:50 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 20:12:52 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	check_fill_pwd(t_lst_env **lst_env)
{
	t_lst_env	*tmp;
	t_lst_env	*new;

	tmp = *lst_env;
	while (tmp)
	{
		if (its_pwd(tmp->line))
			return (1);
		tmp = tmp->next;
	}
	new = ft_lst_new_env();
	if (!new)
		return (0);
	new->line = create_pwd();
	if (!new->line)
		return (0);
	ft_lst_add_back_env(new, lst_env);
	return (1);
}

int	check_fill_shlvl(t_lst_env **lst_env)
{
	t_lst_env	*tmp;
	t_lst_env	*new;

	tmp = *lst_env;
	while (tmp)
	{
		if (its_shlvl(tmp->line))
			return (1);
		tmp = tmp->next;
	}
	new = ft_lst_new_env();
	if (!new)
		return (0);
	new->line = create_shlvl();
	if (!new->line)
		return (0);
	ft_lst_add_back_env(new, lst_env);
	return (1);
}
