/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/11/20 15:12:59 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	convert_list(t_cmd *cmd, t_lst_cmd *cmd_list)
{
	int			i;
	int			size_list;
	t_lst_arg	*start;

	start = cmd_list->arg;
	size_list = ft_lst_size_arg(cmd_list->arg) + 1;
	if (cmd->name != NULL)
		free(cmd->name);//pas freetab parce que free dans liste chainee
	i = 0;
	cmd->name = malloc(sizeof(char *) * size_list);
	if (!cmd->name)
		return ;
	while (cmd_list->arg != NULL)
	{
		if (cmd_list->arg->name != NULL)
		{
			cmd->name[i] = cmd_list->arg->name;
			i++;
		}
		else if (cmd_list->arg->arg != NULL)
		{
			cmd->name[i] = cmd_list->arg->arg;
			i++;
		}
		cmd_list->arg = cmd_list->arg->next;
	}
	cmd->name[i] = NULL;
	cmd_list->arg = start;
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
