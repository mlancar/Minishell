/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/10/05 18:52:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**convert_list(t_lst_argv *argv)
{
	int	i;
	char **argv_name;
	int	size_list;
	t_lst_info	*start;

	start = argv->info;
	size_list = ft_lst_size_info(argv->info) + 1;
	//printf("size list = %d\n", size_list);
	argv_name = NULL;
	i = 0;
	argv_name = malloc(sizeof(char*) * size_list);
	if (!argv_name)
		return (NULL);
	//printf("argv->info->info = %s\n", argv->info->info);
	while (argv->info != NULL)
	{
		if (argv->info->name != NULL)
		{
			argv_name[i] = argv->info->name;
			// printf("argv->info->name = %s\n", argv->info->name);
			// printf("argv_name = %s\n", argv_name[i]);
			i++;
		}
		else if (argv->info->arg != NULL)
		{
			argv_name[i] = argv->info->arg;
			// printf("argv->info->info = %s\n", argv->info->info);
			// printf("argv_info = %s\n", argv_name[i]);
			i++;
		}
		argv->info = argv->info->next;
	}
	argv_name[i] = NULL;
	// i = 0;
	// while (argv_name[i])
	// {
	// 	//printf("argv_name = %s\n", argv_name[i]);
	// 	i++;
	// }
	argv->info = start;
	return (argv_name);
}
