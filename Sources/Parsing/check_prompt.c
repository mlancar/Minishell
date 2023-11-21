/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:15:56 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 17:44:53 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_whitespace(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (prompt[i] >= '\t' && prompt[i] <= '\r'))
		i++;
	if (prompt[i])
		return (0);
	return (1);
}

int	check_prompt(char *prompt)
{
	if (only_whitespace(prompt))
		return (0);
	return (1);
}
