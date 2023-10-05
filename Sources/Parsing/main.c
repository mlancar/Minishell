/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:09 by auferran          #+#    #+#             */
/*   Updated: 2023/10/05 14:25:55 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int infoc, char **infov, char **env)
{
	char	*prompt;

	(void) infov;
	(void) env;
	if (infoc == 1)
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
