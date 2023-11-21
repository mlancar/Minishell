/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:23:56 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 20:09:11 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_and_count_env(char *prompt, int *i, t_struct_strdup *s)
{
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		if (cmp_env(prompt, i, tmp->line))
		{
			count_env(tmp->line, s);
			(*i)--;
			return (1);
		}
		tmp = tmp->next;
	}
	if (!update_i_dollar(prompt, i, s))
		return (0);
	s->void_dollar = 1;
	s->dollar_type = 1;
	return (1);
}

int	check_dollar_count(char *p, int *i, int file, t_struct_strdup *s)
{
	if (file == HD)
		return (1);
	if (in_quote(p, *i, &s->s_q, &s->d_q) && s->s_q == 1)
		return (1);
	if (p[*i] == '$' && p[*i + 1] && p[*i + 1] == '?')
	{
		dollar_query_prep(i, s);
		return (-1);
	}
	else if (p[*i] == '$' && (!p[*i + 1] || \
		(!its_valid_expand(p[*i + 1]) && \
			p[*i + 1] != '"' && p[*i + 1] != '\'')))
		return (1);
	else
	{
		if (!search_and_count_env(p, i, s))
			return (0);
		return (-1);
	}
	return (1);
}

int	search_and_expand_env(char *prompt, int *i, t_struct_strdup *s)
{
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		if (cmp_env(prompt, i, tmp->line))
		{
			expand(s, tmp->line);
			(*i)--;
			return (1);
		}
		tmp = tmp->next;
	}
	if (!update_i_dollar(prompt, i, s))
		return (0);
	s->void_dollar = 1;
	return (1);
}

int	check_dollar_expand(char *p, int *i, int file, t_struct_strdup *s)
{
	int	nb;

	if (file == HD)
		return (1);
	if (in_quote(p, *i, &s->s_q, &s->d_q) && s->s_q == 1)
		return (1);
	if (p[*i] == '$' && p[*i + 1] && p[*i + 1] == '?')
	{
		nb = dollar_query_fill(i, s);
		if (nb == 0)
			return (0);
		if (nb == 1)
			return (-1);
	}
	else if (p[*i] == '$' && (!p[*i + 1] || \
		(!its_valid_expand(p[*i + 1]) && \
			p[*i + 1] != '"' && p[*i + 1] != '\'')))
		return (1);
	else
	{
		if (!search_and_expand_env(p, i, s))
			return (0);
		return (-1);
	}
	return (1);
}
