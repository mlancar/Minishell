/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:15:56 by auferran          #+#    #+#             */
/*   Updated: 2023/11/22 18:21:38 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_whitespace(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (prompt[i] == 32
			|| (prompt[i] >= '\t' && prompt[i] <= '\r')))
	{
		i++;
	}
	if (prompt[i])
		return (0);
	return (1);
}

int	check_prompt(char *prompt)
{
	if (only_whitespace(prompt))
	{
		g_exit = 0;
		return (0);
	}
	return (1);
}
