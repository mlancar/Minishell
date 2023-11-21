/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:47 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 22:43:53 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	valid_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_link(t_lst_env **lst_env, t_lst_env **link)
{
	t_lst_env	*tmp;

	tmp = *lst_env;
	if (tmp == *link)
	{
		*lst_env = (*lst_env)->next;
		free(tmp->line);
		free(tmp);
		return ;
	}
	while (tmp->next)
	{
		if (tmp->next == *link)
		{
			tmp->next = (*link)->next;
			free((*link)->line);
			free(*link);
			return ;
		}
		tmp = tmp->next;
	}
}

void	lets_unset_env(char *str, t_struct_data *s)
{
	int			i;
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		i = 0;
		while (str[i] && tmp->line[i] && tmp->line[i] != '=' \
		&& str[i] == tmp->line[i])
			i++;
		if (!str[i] && tmp->line[i] == '=')
		{
			free_link(&s->lst_env, &tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void	lets_unset_export(char *str, t_struct_data *s)
{
	int			i;
	int			j;
	t_lst_env	*tmp;

	tmp = s->lst_export;
	while (tmp)
	{
		i = 0;
		j = 11;
		while (str[i] && tmp->line[j] && tmp->line[j] != '=' \
		&& str[i] == tmp->line[j])
		{
			i++;
			j++;
		}
		if (!str[i] && (tmp->line[j] == '=' || !tmp->line[j]))
		{
			free_link(&s->lst_export, &tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_struct_data *s)
{
	int	i;

	if (its_option(cmd->name))
	{
		g_exit = 2;
		return (1);
	}
	i = 1;
	while (cmd->name[i])
	{
		if (valid_unset(cmd->name[i]))
		{
			lets_unset_env(cmd->name[i], s);
			lets_unset_export(cmd->name[i], s);
		}
		i++;
	}
	g_exit = 0;
	return (1);
}
