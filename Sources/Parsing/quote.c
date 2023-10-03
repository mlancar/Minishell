/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:29 by auferran          #+#    #+#             */
/*   Updated: 2023/09/25 15:02:34 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_in_quote(int booleen1, int booleen2, int *value1, int *value2)
{
	if (booleen1 == 1 && *value1 == 0)
		*value1 += 1;
	else if (booleen2 == 1 && *value2 == 0)
		*value2 += 1;
	else if (booleen1 == 0 && *value1 == 1)
		*value1 -= 1;
	else if (booleen2 == 0 && *value2 == 1)
		*value2 -= 1;
}

void	swap_x(int *booleen1, int *booleen2, int *x1, int *x2)
{
	if (*booleen1 == 0 && *x1 == 1)
		*x1 -= 1;
	if (*booleen2 == 0 && *x2 == 1)
		*x2 -= 1;
}

void	swap_booleen(int *booleen, int *x)
{
	if (*booleen == 0)
	{
		*booleen += 1;
		*x += 1;
	}
	else if (*booleen == 1)
		*booleen -= 1;
}

int	open_quote(char *str, int i, int s_quote, int d_quote)
{
	char	c;

	if (s_quote == 1)
		c = SINGLE_QUOTE;
	if (d_quote == 1)
		c = DOUBLE_QUOTE;
	if (!str[i + 1])
		return (error("minishell: syntax error open quote\n"), 1);
	if (str[i] != c)
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (error("minishell: syntax error open quote\n"), 1);
}

int	in_quote(char *str, int c, int *in_s_quote, int *in_d_quote)
{
	t_struct_quote	s;

	if (!str)
		return (-1);
	ft_memset(&s, 0, sizeof(t_struct_quote));
	while (str[s.i])
	{
		swap_x(&s.s_quote, &s.d_quote, &s.x_s, &s.x_d);
		if (str[s.i] == '\'' && s.d_quote == 0)
			swap_booleen(&s.s_quote, &s.x_s);
		if (str[s.i] == '"' && s.s_quote == 0)
			swap_booleen(&s.d_quote, &s.x_d);
		if (s.i == c && (s.s_quote == 1 || s.d_quote == 1))
			if (open_quote(str, s.i, s.s_quote, s.d_quote))
				return (-1);
		if (s.i == c && (s.x_s == 1 || s.x_d == 1))
		{
			value_in_quote(s.x_s, s.x_d, in_s_quote, in_d_quote);
			return (1);
		}
		s.i++;
	}
	return (0);
}
