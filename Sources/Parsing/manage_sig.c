/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:24 by auferran          #+#    #+#             */
/*   Updated: 2023/11/14 19:29:42 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_exit = 130;
		ft_putstr("\n(auferran&malancar)-[~/minishell]$ ");
	}
}

int	manage_sig()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
