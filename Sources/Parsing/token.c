/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:24:11 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 19:37:12 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token(char *prompt, int i)
{
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	if (prompt[i] == '<' && !in_quote(prompt, i, &s_q, &d_q))
		return (1);
	else if (prompt[i] == '>' && !in_quote(prompt, i, &s_q, &d_q))
		return (1);
	else if (prompt[i] == '|' && !in_quote(prompt, i, &s_q, &d_q))
		return (1);
	return (0);
}

int	check_reverse_file(char *prompt, int i)
{
	if (prompt[i + 1] && (prompt[i + 1] == '<' || prompt[i + 1] == '>') \
		&& prompt[i] != prompt[i + 1])
	{
		g_exit = 2;
		return (error \
			("minishell: syntax error near unexpected token `newline'\n"), 0);
	}
	return (1);
}
