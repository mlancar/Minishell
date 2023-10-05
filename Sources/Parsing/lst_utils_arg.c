/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:15 by auferran          #+#    #+#             */
/*   Updated: 2023/09/25 15:04:52 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_size_info(t_lst_info *info)
{
	int			i;

	if (!info)
		return (0);
	i = 0;
	while (info != NULL)
	{
		info = info->next;
		i++;
	}
	return (i);
}

void	ft_lst_clear_info(t_lst_info **info)
{
	int			i;
	int			size;
	t_lst_info	*tmp;

	if (!(*info))
		return ;
	i = 0;
	size = ft_lst_size_info(*info);
	while (i < size)
	{
		tmp = (*info)->next;
		free(*info);
		*info = tmp;
		i++;
	}
	*info = NULL;
}

t_lst_info	*ft_lst_last_info(t_lst_info *info)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lst_size_info(info);
	while (i < size - 1)
	{
		info = info->next;
		i++;
	}
	return (info);
}

void	ft_lst_add_back_info(t_lst_info *info_new, t_lst_info **info)
{
	t_lst_info	*tmp;

	if (!(*info))
	{
		*info = info_new;
		return ;
	}
	tmp = ft_lst_last_info(*info);
	tmp->next = info_new;
}

t_lst_info	*ft_lst_new_info(void)
{
	t_lst_info	*lst_new;

	lst_new = malloc(sizeof(t_lst_info));
	if (!lst_new)
		return (error("MALLOC FAILURE\n"), NULL);
	ft_memset(lst_new, 0, sizeof(t_lst_info));
	return (lst_new);
}
