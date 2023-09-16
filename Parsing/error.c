/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:00 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 17:16:01 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int nb)
{
	if (nb == ERROR_MALLOC)
		printf("Malloc Failure ?\n");
	if (nb == ERROR_PROMPT)
		printf("Error syntax ?\n");
}
