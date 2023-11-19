/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:58:55 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 20:59:37 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_arg_name(char *prompt, t_lst_arg **arg, int *i, t_lst_env *lst_env)
{
	int			nb;
	t_lst_arg	*new;

	new = ft_lst_new_arg();
	if (!new)
		return (0);
	nb = 0;
	new->name = dup_str(prompt, i, &nb, lst_env);
	if (!new->name)
		return (ft_lst_clear_arg(&new), 0);
	if (nb == -1)
	{
		free(new->name);
		new->name = NULL;
	}
	ft_lst_add_back_arg(new, arg);
	return (1);
}

int	fill_arg_arg(char *prompt, t_lst_arg **arg, int *i, t_lst_env *lst_env)
{
	int			nb;
	t_lst_arg	*new;

	new = ft_lst_new_arg();
	if (!new)
		return (0);
	nb = 0;
	new->arg = dup_str(prompt, i, &nb, lst_env);
	if (!new->arg)
		return (ft_lst_clear_arg(&new), 0);
	if (nb == -1)
	{
		free(new->arg);
		new->arg = NULL;
	}
	ft_lst_add_back_arg(new, arg);
	return (1);
}

int	fill_arg(char *prompt, t_lst_arg **arg, int *i, t_lst_env *lst_env)
{
	if (ft_lst_size_arg(*arg) == 0)
	{
		if (!fill_arg_name(prompt, arg, i, lst_env))
			return (0);
	}
	else if (ft_lst_size_arg(*arg) > 0)
	{
		if (!fill_arg_arg(prompt, arg, i, lst_env))
			return (0);
	}
	return (1);
}
