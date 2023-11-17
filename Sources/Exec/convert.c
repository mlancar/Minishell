/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:05:44 by malancar          #+#    #+#             */
/*   Updated: 2023/11/17 18:56:56 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	convert_list(t_cmd *cmd, t_lst_cmd *argv)
{
	int			i;
	int			size_list;
	t_lst_arg	*start;

	start = argv->arg;
	size_list = ft_lst_size_arg(argv->arg) + 1;
	if (cmd->argv != NULL)
		free(cmd->argv);//pas freetab parce que free dans liste chainee
	i = 0;
	cmd->argv = malloc(sizeof(char *) * size_list);
	if (!cmd->argv)
		return ;
	while (argv->arg != NULL)
	{
		if (argv->arg->name != NULL)
		{
			cmd->argv[i] = argv->arg->name;
			i++;
		}
		else if (argv->arg->arg != NULL)
		{
			cmd->argv[i] = argv->arg->arg;
			i++;
		}
		argv->arg = argv->arg->next;
	}
	cmd->argv[i] = NULL;
	argv->arg = start;
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
