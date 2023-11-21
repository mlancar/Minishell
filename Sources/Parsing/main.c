/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:09 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 18:25:52 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	g_exit;

char	*init_prompt(void)
{
	char	*prompt;

	if (!isatty(0))
		prompt = get_next_line(0, 0);
	else
		prompt = readline("(auferran&malancar)-$ ");
	add_history(prompt);
	if (!prompt)
	{
		ft_putstr("exit\n");
		return (NULL);
	}
	return (prompt);
}

int	main(int argc, char **cmd_list, char **env)
{
	t_struct_data	s;

	(void) cmd_list;
	ft_memset(&s, 0, sizeof(t_struct_data));
	init_lst_env(env, &s);
	if (argc == 1)
	{
		while (1)
		{
			manage_sig();
			s.prompt = init_prompt();
			if (!s.prompt)
			{
				free_parsing(&s);
				exit(g_exit);
			}
			manage(s.prompt, &s);
			free(s.prompt);
		}
		free_parsing(&s);
	}
	return (0);
}
