/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:21:58 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 20:11:34 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_value(int *i, t_struct_strdup *s)
{
	if (s->file_type == 1)
	{
		*i = s->index_file;
		if (s->dollar_type == 1)
			s->len += s->len_env;
	}
	else if (s->dollar_type == 1)
	{
		*i = s->after_space;
		s->len += s->len_env;
	}
	if (s->dollar_type == 0 && s->file_type == 0)
	{
		*i -= s->len;
		*i -= s->count;
	}
}

int	count_c(char *prompt, char c, int *i, t_struct_strdup *s)
{
	int	count;

	count = 0;
	while (prompt[*i] && prompt[*i] == c)
	{
		count++;
		(*i)++;
	}
	if (count > 2)
	{
		g_exit = 2;
		return (error("minishell: syntax error near unexpected token\n"), 0);
	}
	while (prompt[*i] && prompt[*i] == ' ')
		(*i)++;
	if (!prompt[*i] || token(prompt, *i))
	{
		g_exit = 2;
		return (\
		error("minishell: syntax error near unexpected token `newline'\n"), 0);
	}
	s->file_type = 1;
	s->index_file = *i;
	return (1);
}

int	prep_malloc(char *prompt, t_struct_strdup *s, int *i, int nb)
{
	while (prompt[*i] && !token(prompt, *i))
	{
		if (prompt[*i] == ' ' && !in_quote(prompt, *i, &s->s_q, &s->d_q))
			break ;
		if (!update_quote(prompt, *i, s))
			return (0);
		if (prompt[*i] == '$')
		{
			s->nb_fill = check_dollar_count(prompt, i, nb, s);
			if (s->nb_fill == 0)
				return (0);
			if (s->nb_fill == 1)
				s->len++;
		}
		else if (prompt[*i] && prompt[*i] == s->c)
			s->count++;
		else if (prompt[*i])
			s->len++;
		(*i)++;
	}
	return (1);
}

int	fill_str(char *prompt, t_struct_strdup *s, int *i, int nb)
{
	while (prompt[*i] && !token(prompt, *i))
	{
		if (prompt[*i] == ' ' && !in_quote(prompt, *i, &s->s_q, &s->d_q))
			break ;
		if (!update_quote(prompt, *i, s))
			return (0);
		if (prompt[*i] == '$')
		{
			s->nb_fill = check_dollar_expand(prompt, i, nb, s);
			if (s->nb_fill == 0)
				return (0);
			if (s->nb_fill == 1)
				s->str[s->j++] = prompt[*i];
		}
		else if (prompt [*i] && prompt[*i] != s->c)
			s->str[s->j++] = prompt[*i];
		(*i)++;
	}
	s->str[s->j] = 0;
	return (1);
}

char	*dup_str(char *prompt, int *i, int *nb, t_lst_env *lst_env)
{
	t_struct_strdup	s;

	ft_memset(&s, 0, sizeof(t_struct_strdup));
	s.after_space = *i;
	s.lst_env = lst_env;
	if (*nb >= FILE)
		if (!count_c(prompt, prompt[*i], i, &s))
			return (NULL);
	while (prompt[*i] && its_white_space(prompt[*i]))
		(*i)++;
	if (!prep_malloc(prompt, &s, i, *nb))
		return (NULL);
	update_value(i, &s);
	s.str = malloc(sizeof(char) * s.len + 1);
	if (!s.str)
		return (error("MALLOC FAILURE\n"), NULL);
	if (!fill_str(prompt, &s, i, *nb))
		return (free(s.str), NULL);
	if (s.void_dollar == 1)
		*nb = -1;
	return (s.str);
}
