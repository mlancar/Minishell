/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:15 by auferran          #+#    #+#             */
/*   Updated: 2023/10/11 15:25:19 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_size_arg(t_lst_arg *arg)
{
	int			i;

	if (!arg)
		return (0);
	i = 0;
	while (arg != NULL)
	{
		arg = arg->next;
		i++;
	}
	return (i);
}

t_lst_arg	*ft_lst_last_arg(t_lst_arg *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lst_size_arg(arg);
	while (i < size - 1)
	{
		arg = arg->next;
		i++;
	}
	return (arg);
}

void	ft_lst_add_back_arg(t_lst_arg *arg_new, t_lst_arg **arg)
{
	t_lst_arg	*tmp;

	if (!(*arg))
	{
		*arg = arg_new;
		return ;
	}
	tmp = ft_lst_last_arg(*arg);
	tmp->next = arg_new;
}

t_lst_arg	*ft_lst_new_arg(void)
{
	t_lst_arg	*lst_new;

	lst_new = malloc(sizeof(t_lst_arg));
	if (!lst_new)
		return (error("MALLOC FAILURE\n"), NULL);
	ft_memset(lst_new, 0, sizeof(t_lst_arg));
	return (lst_new);
}
