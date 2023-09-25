/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:10:25 by auferran          #+#    #+#             */
/*   Updated: 2023/09/21 17:19:26 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_prompt(char *prompt)
{
	t_lst_cmd	*cmd;

	cmd = NULL;
	if (!init_lst(prompt, &cmd))
		return (0);
	if (!check_prompt(prompt, cmd))
		return (1);
	//PAS OUBLIER DE FREE
	return (1);

}

void	minishell(char **env)
{
	char		*prompt;

	(void) env;
	manage_sig();
	while (1)
	{
		prompt = readline("(auferran&malancar)-[~/minishell]$ ");
		if (!prompt || !ft_strcmp_unsigned("exit", prompt))
		{
			if (!ft_strcmp_unsigned("exit", prompt))
				free(prompt);
			printf("exit\n");
			return ;
		}
		else if (prompt && !manage_prompt(prompt))
		{
			free(prompt);
			return ;
		}
		free(prompt);
	}
}
