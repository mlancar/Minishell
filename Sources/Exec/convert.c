/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/10/24 16:35:31 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**convert_list(t_lst_cmd *argv)
{
	int	i;
	char **argv_name;
	int	size_list;
	t_lst_arg	*start;

	start = argv->arg;
	size_list = ft_lst_size_arg(argv->arg) + 1;
	argv_name = NULL;
	i = 0;
	argv_name = malloc(sizeof(char*) * size_list);
	if (!argv_name)
		return (NULL);
	while (argv->arg != NULL)
	{
		if (argv->arg->name != NULL)
		{
			argv_name[i] = argv->arg->name;
			i++;
		}
		else if (argv->arg->arg != NULL)
		{
			argv_name[i] = argv->arg->arg;
			i++;
		}
		argv->arg = argv->arg->next;
	}
	argv_name[i] = NULL;
	argv->arg = start;
	return (argv_name);
}

char	**convert_list_env(t_struct_env *s)
{
	int				i;
	char 			**env;
	int				size_list;
	t_lst_env	*start;

	start = s->lst_env;
	size_list = ft_lst_size_env(s->lst_env) + 1;
	env = NULL;
	i = 0;
	env = malloc(sizeof(char*) * size_list);
	if (!env)
		return (NULL);
	while (s->lst_env != NULL)
	{
		if (s->lst_env->line != NULL)
		{
			env[i] = s->lst_env->line;
			i++;
		}
		s->lst_env = s->lst_env->next;
	}
	env[i] = NULL;
	s->lst_env = start;
	return (env);
}
