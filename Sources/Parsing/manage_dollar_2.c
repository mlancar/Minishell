/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:39:03 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 19:48:29 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_i_dollar(char *prompt, int *i, t_struct_strdup *s)
{
	(*i)++;
	if (!update_quote(prompt, *i, s))
		return (0);
	if (ft_isdigit(prompt[*i]) || prompt[*i] == '"' || prompt[*i] == '\'')
		(*i)++;
	else
	{
		while (prompt[*i] && its_valid_expand(prompt[*i]))
			(*i)++;
	}
	(*i)--;
	return (1);
}

int	cmp_env(char *str, int *i, char *line)
{
	int	x;
	int	j;

	x = *i + 1;
	j = 0;
	while (str[x] && its_valid_expand(str[x]) && line[j] && str[x] == line[j])
	{
		x++;
		j++;
	}
	if ((!str[x] || !its_valid_expand(str[x])) && line[j] == '=')
	{
		*i = x;
		return (1);
	}
	return (0);
}

void	count_env(char *line, t_struct_strdup *s)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		s->len_env++;
		i++;
	}
	s->dollar_type = 1;
}

void	expand(t_struct_strdup *s, char *line)
{
	int	i;

	i = strlen_env(line) + 1;
	while (line[i])
	{
		s->str[s->j] = line[i];
		s->j++;
		i++;
	}
	s->dollar_type = 0;
}
