/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/10/02 17:28:05 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**convert(t_lst_cmd *cmd)
{
	int	i;
	char **cmd_name;
	int	size_list;
	t_lst_arg	*start;
	
	start = cmd->arg;
	size_list = ft_lst_size_arg(cmd->arg) + 1;
	//printf("size list = %d\n", size_list);
	cmd_name = NULL;
	i = 0;
	cmd_name = malloc(sizeof(char*) * size_list);
	if (!cmd_name)
		return (NULL);
	while (cmd->arg != NULL)
	{
		if (cmd->arg->name != NULL)
		{
			cmd_name[i] = cmd->arg->name;
			//printf("cmd_name = %s\n", cmd_name[i]);
			i++;
		}
		else if (cmd->arg->arg != NULL)
		{
			cmd_name[i] = cmd->arg->arg;
			//printf("cmd_name %p = %s\n", &cmd_name[i], cmd_name[i]);
			i++;
		}
		cmd->arg = cmd->arg->next;
	}
	cmd_name[i] = NULL;
	// i = 0;
	// while (cmd_name[i])
	// {
	// 	//printf("cmd_name = %s\n", cmd_name[i]);
	// 	i++;
	// }
	cmd->arg = start;
	if (cmd != NULL)
		cmd = cmd->next;
	return (cmd_name);
}


int	init_struct(t_pipex *pipex_cmd, t_lst_cmd *cmd)
{
	pipex_cmd->infile = 0;
	pipex_cmd->outfile = 1;
	//printf("cmd->file->limiter = %p\n", &cmd->file->limiter);
	if (cmd->file)
	{
		pipex_cmd->if_here_doc = 1;
		
		pipex_cmd->max = ft_lst_size_arg(cmd->arg);
		if (cmd->file->outfile)
			open_outfile(pipex_cmd, cmd->file->outfile);
		else
			pipex_cmd->outfile = 1;
	}
	else if (cmd->file == NULL)
	{
		pipex_cmd->if_here_doc = 0;
		if (cmd->file)
		{
			if (cmd->file->infile)
				open_infile(pipex_cmd, cmd->file->infile);
			else if (!cmd->file->infile)
				pipex_cmd->infile = 0;
			if (cmd->file->outfile)
				open_outfile(pipex_cmd, cmd->file->outfile);
			else if (!cmd->file->outfile)
				pipex_cmd->outfile = 1;
		}
		//printf("cmd max = %d\n", pipex_cmd->max);
	}
	else
		return (0);
	pipex_cmd->max = ft_lst_size_arg(cmd->arg) -1;
	pipex_cmd->index = 0;
	pipex_cmd->index_pid = 1;
	pipex_cmd->first = 1;
	pipex_cmd->path = NULL;
	pipex_cmd->last = pipex_cmd->max;
	return (1);
}