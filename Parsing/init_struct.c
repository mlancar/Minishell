/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:10:15 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 17:10:17 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_nb_cmd(char *prompt)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

int	init_struct(char *prompt, s_env_pipex **env_pipex)
{
	int	nb_cmd;

	nb_cmd = check_nb_cmd(prompt) + 1;
	*env_pipex = malloc(sizeof(s_env_pipex) * nb_cmd);
	if (!env_pipex)
		return (0);
	ft_memset(*env_pipex, 0, sizeof(s_env_pipex) * nb_cmd);
	return (1);
}
