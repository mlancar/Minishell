/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/10/16 16:21:22 by malancar         ###   ########.fr       */
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
