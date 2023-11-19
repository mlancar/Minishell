/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:24:06 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 17:24:07 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_quote(char *prompt, int i, t_struct_strdup *s)
{
	s->s_q = 0;
	s->d_q = 0;
	if ((in_quote(prompt, i, &s->s_q, &s->d_q)) == -1)
		return (0);
	if (s->s_q == 1)
		s->c = SINGLE_QUOTE;
	else if (s->d_q == 1)
		s->c = DOUBLE_QUOTE;
	return (1);
}
