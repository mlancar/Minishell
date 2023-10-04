/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/10/04 20:13:38 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**convert(t_lst_cmd *argv)
{
	int	i;
	char **argv_name;
	int	size_list;
	t_lst_info	*start;

	dprintf(2, "ici %p\n", argv->info);
	dprintf(2, "la %p\n", argv);

	start = argv->info;
	size_list = ft_lst_size_arg(argv->info) + 1;
	//printf("size list = %d\n", size_list);
	argv_name = NULL;
	i = 0;
	argv_name = malloc(sizeof(char*) * size_list);
	if (!argv_name)
		return (NULL);
	//printf("argv->arg->arg = %s\n", argv->arg->arg);
	while (argv->info != NULL)
	{
		if (argv->info->name != NULL)
		{
			argv_name[i] = argv->info->name;
			//printf("argv->info->name = %s\n", argv->info->name);
			// printf("argv_name = %s\n", argv_name[i]);
			i++;
		}
		else if (argv->info->arg != NULL)
		{
			argv_name[i] = argv->info->arg;
			//printf("argv->info->arg = %s\n", argv->info->arg);
			// printf("argv_arg = %s\n", argv_name[i]);
			i++;
		}
		argv->info = argv->info->next;
	}
	argv_name[i] = NULL;
	argv->info = start;
	return (argv_name);
}

int	init_struct(t_pipex *cmd, t_lst_cmd *argv)
{
	cmd->infile = 0;
	cmd->outfile = 1;
	//printf("cmd->file->limiter = %p\n", &cmd->file->limiter);
	if (argv->file)
	{
		cmd->if_here_doc = 1;
		
		cmd->max = ft_lst_size_arg(argv->info);
		if (argv->file->outfile)
			open_outfile(cmd, argv->file->outfile);
		else
			cmd->outfile = 1;
	}
	else if (argv->file == NULL)
	{
		cmd->if_here_doc = 0;
		if (argv->file)
		{
			if (argv->file->infile)
				open_infile(cmd, argv->file->infile);
			else if (!argv->file->infile)
				cmd->infile = 0;
			if (argv->file->outfile)
				open_outfile(cmd, argv->file->outfile);
			else if (!argv->file->outfile)
				cmd->outfile = 1;
		}
	}
	else
		return (0);
	cmd->max = list_size(argv);
	//argv->info->fd_next = -1;
	//argv->info->fd_prev = -1;
	//printf("cmd max = %d\n", cmd->max);
	cmd->index = 0;
	cmd->index_pid = 0;
	cmd->first = 0;
	cmd->path = NULL;
	cmd->last = cmd->max;
	return (1);
}