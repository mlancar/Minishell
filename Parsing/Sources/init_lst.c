/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:10:15 by auferran          #+#    #+#             */
/*   Updated: 2023/09/21 16:27:03 by malancar         ###   ########.fr       */
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

int	init_lst(char *prompt, t_lst_cmd **cmd)
{
	int			i;
	int			nb_cmd;
	t_lst_cmd	*new;

	i = 0;
	nb_cmd = check_nb_cmd(prompt) + 1;
	while (i < nb_cmd)
	{
		new = ft_lst_new(pipex);
		if (!new)
			return (0);
		ft_lst_add_back(new, pipex);
	}
	//ft_memset(*env_pipex, 0, sizeof(s_env_pipex) * nb_cmd);
	return (1);
}
