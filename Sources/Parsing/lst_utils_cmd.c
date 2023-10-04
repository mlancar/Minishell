/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:04:47 by auferran          #+#    #+#             */
/*   Updated: 2023/09/25 15:35:11 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_size_cmd(t_lst_cmd *argv)
{
	int			i;

	if (!argv)
		return (0);
	i = 0;
	while (argv != NULL)
	{
		argv = argv->next;
		i++;
	}
	return (i);
}

void	ft_lst_clear_cmd(t_lst_cmd **argv)
{
	int			i;
	int			size;
	t_lst_cmd	*tmp;

	if (!(*argv))
		return ;
	i = 0;
	size = ft_lst_size_cmd(*argv);
	while (i < size)
	{
		tmp = (*argv)->next;
		free(*argv);
		*argv = tmp;
		i++;
	}
	*argv = NULL;
}

t_lst_cmd	*ft_lst_last_cmd(t_lst_cmd *argv)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lst_size_cmd(argv);
	while (i < size - 1)
	{
		argv = argv->next;
		i++;
	}
	return (argv);
}

void	ft_lst_add_back_cmd(t_lst_cmd *lst_new, t_lst_cmd **argv)
{
	t_lst_cmd	*tmp;

	if (!(*argv))
	{
		*argv = lst_new;
		return ;
	}
	tmp = ft_lst_last_cmd(*argv);
	tmp->next = lst_new;
}

t_lst_cmd	*ft_lst_new_cmd(void)
{
	t_lst_cmd	*lst_new;

	lst_new = malloc(sizeof(t_lst_cmd));
	if (!lst_new)
		return (error("MALLOC FAILURE\n"), NULL);
	ft_memset(lst_new, 0, sizeof(t_lst_cmd));
	return (lst_new);
}
