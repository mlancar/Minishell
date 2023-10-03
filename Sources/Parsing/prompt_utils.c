/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:03:15 by auferran          #+#    #+#             */
/*   Updated: 2023/09/25 16:00:20 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_white_space(char c)
{
	if (c == ' ' || c == '\r' || c == '\t')
		return (1);
	return (0);
}

int	its_file(char c)
{
	if (c == '<')
		return (1);
	if (c == '>')
		return (2);
	return (0);
}
