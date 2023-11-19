/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:23:50 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 23:35:33 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	strlen_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	its_valid_expand(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
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
