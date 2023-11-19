/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:23:38 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 23:33:00 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_size_env(t_lst_env *lst_env)
{
	int			i;

	if (!lst_env)
		return (0);
	i = 0;
	while (lst_env != NULL)
	{
		lst_env = lst_env->next;
		i++;
	}
	return (i);
}

void	ft_lst_clear_env(t_lst_env **lst_env)
{
	int			i;
	int			size;
	t_lst_env	*tmp;

	if (!(*lst_env))
		return ;
	i = 0;
	size = ft_lst_size_env(*lst_env);
	while (i < size)
	{
		if ((*lst_env)->line)
			free((*lst_env)->line);
		tmp = (*lst_env)->next;
		free(*lst_env);
		*lst_env = tmp;
		i++;
	}
	*lst_env = NULL;
}

t_lst_env	*ft_lst_last_env(t_lst_env *lst_env)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lst_size_env(lst_env);
	while (i < size - 1)
	{
		lst_env = lst_env->next;
		i++;
	}
	return (lst_env);
}

void	ft_lst_add_back_env(t_lst_env *env_new, t_lst_env **lst_env)
{
	t_lst_env	*tmp;

	if (!(*lst_env))
	{
		*lst_env = env_new;
		return ;
	}
	tmp = ft_lst_last_env(*lst_env);
	tmp->next = env_new;
}

t_lst_env	*ft_lst_new_env(void)
{
	t_lst_env	*lst_new;

	lst_new = malloc(sizeof(t_lst_env));
	if (!lst_new)
		return (error("MALLOC FAILURE\n"), NULL);
	ft_memset(lst_new, 0, sizeof(t_lst_env));
	return (lst_new);
}
