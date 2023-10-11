/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/10/11 15:31:18 by malancar         ###   ########.fr       */
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
	//printf("size list = %d\n", size_list);
	argv_name = NULL;
	i = 0;
	argv_name = malloc(sizeof(char*) * size_list);
	if (!argv_name)
		return (NULL);
	//printf("argv->arg->arg = %s\n", argv->arg->arg);
	while (argv->arg != NULL)
	{
		if (argv->arg->name != NULL)
		{
			argv_name[i] = argv->arg->name;
			// printf("argv->arg->name = %s\n", argv->arg->name);
			// printf("argv_name = %s\n", argv_name[i]);
			i++;
		}
		else if (argv->arg->arg != NULL)
		{
			argv_name[i] = argv->arg->arg;
			// printf("argv->arg->arg = %s\n", argv->arg->arg);
			// printf("argv_arg = %s\n", argv_name[i]);
			i++;
		}
		argv->arg = argv->arg->next;
	}
	argv_name[i] = NULL;
	// i = 0;
	// while (argv_name[i])
	// {
	// 	//printf("argv_name = %s\n", argv_name[i]);
	// 	i++;
	// }
	argv->arg = start;
	return (argv_name);
}
