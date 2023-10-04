/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:09 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 20:04:49 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*prompt;

	(void) argv;
	(void) env;
	if (argc == 1)
	{
		manage_sig();
		while (1)
		{
			prompt = readline("(auferran&malancar)-[~/minishell]$ ");
			if (!prompt || !ft_strcmp("exit", prompt))
			{
				if (!ft_strcmp("exit", prompt))
					free(prompt);
				printf("exit\n");
				return (0) ;
			}
			else if (prompt && !manage(prompt, env))
			{
				free(prompt);
				return (0) ;
			}
			free(prompt);
		}
	}
	return (0);
}
