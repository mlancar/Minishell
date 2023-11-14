/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:09 by auferran          #+#    #+#             */
/*   Updated: 2023/11/14 19:13:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	g_exit;

int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	t_struct_env	s;

	(void) argv;
	prompt = NULL;
	ft_memset(&s, 0, sizeof(t_struct_env));
	init_lst_env(env, &s);
	if (argc == 1)
	{
		while (1)
		{
			manage_sig();
			if (!isatty(0))
				prompt = get_next_line(0, 0);
			else
				prompt = readline("(auferran&malancar)-[~/minishell]$ ");
			add_history(prompt);
			if (!prompt)
			{
				ft_putstr("exit\n");
				break;
			}
			manage(prompt, &s);
			free(prompt);
		}
		if (prompt)
			free(prompt);
		rl_clear_history();
		ft_lst_clear_env(&s.lst_env);
		ft_lst_clear_env(&s.lst_export);
	}
	return (0);
}
