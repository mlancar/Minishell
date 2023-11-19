/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:23:56 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 23:34:39 by auferran         ###   ########.fr       */
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
	(*i)++;
	while (prompt[*i] && its_valid_expand(prompt[*i]))
		(*i)++;
	(*i)--;
	s->dollar_type = 1;
	return (0);
}

int	check_dollar_count(char *prompt, int *i, int file, t_struct_strdup *s)
{
	if (file == HD)
		return (1);
	if (in_quote(prompt, *i, &s->s_q, &s->d_q) && s->s_q == 1)
		return (1);
	if (prompt[*i] == '$' && prompt[*i + 1] && prompt[*i + 1] == '?')
	{
		dollar_query_prep(i, s);
		return (-1);
	}
	else if (prompt[*i] == '$' && (!prompt[*i + 1] || \
	!its_valid_expand(prompt[*i + 1])))
	{
		s->void_dollar = 1;
		return (1);
	}
	else
	{
		search_and_count_env(prompt, i, s);
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
	(*i)++;
	while (prompt[*i] && its_valid_expand(prompt[*i]))
		(*i)++;
	(*i)--;
	s->void_dollar = 1;
	return (0);
}

int	check_dollar_expand(char *prompt, int *i, int file, t_struct_strdup *s)
{
	int	nb;

	if (file == HD)
		return (1);
	if (in_quote(prompt, *i, &s->s_q, &s->d_q) && s->s_q == 1)
		return (1);
	if (prompt[*i] == '$' && prompt[*i + 1] && prompt[*i + 1] == '?')
	{
		nb = dollar_query_fill(i, s);
		if (nb == 0)
			return (0);
		if (nb == 1)
			return (-1);
	}
	else if (prompt[*i] == '$' && (!prompt[*i + 1] || \
	!its_valid_expand(prompt[*i + 1])))
		return (1);
	else
	{
		search_and_expand_env(prompt, i, s);
		return (-1);
	}
	return (1);
}
