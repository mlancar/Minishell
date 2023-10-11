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
	char		*prompt;
	t_lst_env	*lst_env;

	(void) argv;
	prompt = NULL;
	lst_env = NULL;
	init_lst_env(env, &lst_env);
	if (argc == 1)
	{
		manage_sig();
		while (1)
		{
			prompt = readline("(auferran&malancar)-[~/minishell]$ ");
			add_history(prompt);
			if (!prompt)
			{
				printf("exit\n");
				break;
			}
			manage(prompt, env, &lst_env);
			free(prompt);
		}
		if (prompt)
			free(prompt);
		rl_clear_history();
		ft_lst_clear_env(&lst_env);
	}
	return (0);
}
