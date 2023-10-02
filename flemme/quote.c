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

int	count_quote(char *str, int nb)
{
	int	i;
	int	nb_quote;
	int	type_quote;

	i = 0;
	nb_quote = 0;
	type_quote = 0;
	if (nb == SINGLE_QUOTE)
		type_quote = 39;
	if (nb == DOUBLE_QUOTE)
		type_quote = 34;
	while (str[i])
	{
		if (str[i] == type_quote)
			nb_quote++;
		i++;
	}
	return (nb_quote);
}

void	value_in_quote(int booleen1, int booleen2, int *value1, int *value2)
{
	if (booleen1 == 1 && *value1 == 0)
		*value1 += 1;
	if (booleen2 == 1 && *value2 == 0)
		*value2 += 1;
	if (booleen1 == 0 && *value1 == 1)
		*value1 -= 1;
	if (booleen2 == 0 && *value2 == 1)
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
		if (s.i == c && (s.x_s == 1 || s.x_d == 1))
		{
			value_in_quote(s.x_s, s.x_d, in_s_quote, in_d_quote);
			return (1);
		}
		s.i++;
	}
	return (0);
}
