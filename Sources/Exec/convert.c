/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:58:56 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	convert_list(t_cmd *cmd, t_lst_cmd *cmd_list)
{
	int			i;
	t_lst_arg	*list_tmp;

	list_tmp = cmd_list->arg;
	if (cmd->name != NULL)
		free(cmd->name);
	i = 0;
	cmd->name = malloc(sizeof(char *) * (ft_lst_size_arg(cmd_list->arg) + 1));
	if (!cmd->name)
		return ;
	while (list_tmp != NULL)
	{
		if (list_tmp->name != NULL)
		{
			cmd->name[i] = list_tmp->name;
			i++;
		}
		else if (list_tmp->arg != NULL)
		{
			cmd->name[i] = list_tmp->arg;
			i++;
		}
		list_tmp = list_tmp->next;
	}
	cmd->name[i] = NULL;
}

void	convert_list_env(t_cmd *cmd, t_struct_data *s)
{
	int			i;
	int			size_list;
	t_lst_env	*start;

	start = s->lst_env;
	size_list = ft_lst_size_env(s->lst_env) + 1;
	cmd->env = NULL;
	i = 0;
	cmd->env = malloc(sizeof(char *) * size_list);
	if (!cmd->env)
		return ;
	while (s->lst_env != NULL)
	{
		if (s->lst_env->line != NULL)
		{
			cmd->env[i] = s->lst_env->line;
			i++;
		}
		s->lst_env = s->lst_env->next;
	}
	cmd->env[i] = NULL;
	s->lst_env = start;
}
