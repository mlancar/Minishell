/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:24 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 17:16:24 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		printf("\n(auferran&malancar)-[~/minishell]$ ");
}

int	manage_sig()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
