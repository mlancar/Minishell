/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:24:06 by malancar          #+#    #+#             */
/*   Updated: 2023/11/22 21:07:39 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		ft_singleton(1, NULL, NULL, NULL);
		get_next_line(0, 1);
		exit(130);
	}
}
