/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:22:38 by malancar          #+#    #+#             */
/*   Updated: 2023/09/28 17:34:01 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_struct_pipex(t_pipex *pipex_cmd, int ac)
{
	if ((ft_strcmp("here_doc", pipex_cmd->argv[1]) == 0) && (ac > 5))
	{
		pipex_cmd->if_here_doc = 1;
		pipex_cmd->index = 3;
		pipex_cmd->max = ac - 4;
		open_outfile(pipex_cmd, pipex_cmd->argv[ac - 1]);
	}
	else if ((ft_strcmp("here_doc", pipex_cmd->argv[1]) != 0) && (ac > 4))
	{
		pipex_cmd->if_here_doc = 0;
		open_infile(pipex_cmd, pipex_cmd->argv[1]);
		open_outfile(pipex_cmd, pipex_cmd->argv[ac - 1]);
		pipex_cmd->index = 2;
		pipex_cmd->max = ac - 3;
	}
	else
		return (0);
	pipex_cmd->index_pid = 1;
	pipex_cmd->first = 1;
	pipex_cmd->path = NULL;
	pipex_cmd->name = NULL;
	pipex_cmd->last = pipex_cmd->max;
	return (1);
}
