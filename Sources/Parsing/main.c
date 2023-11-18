/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:09 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 23:07:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	g_exit;

char	*init_prompt()
{
	char	*prompt;

	if (!isatty(0))
		prompt = get_next_line(0, 0);
	else
		prompt = readline("(auferran&malancar)-[~/minishell]$ ");
	if (prompt)
		add_history(prompt);
	if (!prompt)
	{
		ft_putstr("exit\n");
			return (NULL);
	}
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	t_struct_data	s;

	(void) argv;
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
				free_all(&s);
				exit(g_exit);
			}
			manage(s.prompt, &s);
			free(s.prompt);
		}
		free_all(&s);
	}
	return (0);
}
