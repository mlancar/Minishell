/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:04 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 16:21:35 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dest_env(char ***dest)
{
	int	i;

	i = 0;
	while (*dest[i])
	{
		free(*dest[i]);
		dest[i] = NULL;
		i++;
	}
	free(*dest);
	*dest = NULL;
}

void	free_my_env(char **my_env)
{
	int	i;

	i = 0;
	while (my_env[i])
	{
		free(my_env[i]);
		my_env[i] = NULL;
		i++;
	}
	free(my_env);
	my_env = NULL;
}

void	free_all(t_struct_data *s)
{	if (s->prompt)
		free(s->prompt);
	if (s->my_env)
		free_my_env(s->my_env);
	rl_clear_history();
	ft_lst_clear_cmd(&s->cmd);
	ft_lst_clear_env(&s->lst_env);
	ft_lst_clear_env(&s->lst_export);
}
