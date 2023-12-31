/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:42 by auferran          #+#    #+#             */
/*   Updated: 2023/11/22 15:38:49 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	doublon_var_content(char *str, t_lst_env *lst_env)
{
	int	i;

	while (lst_env)
	{
		i = 0;
		while (lst_env->line[i] && str[i])
		{
			if (lst_env->line[i] != str[i])
				break ;
			i++;
		}
		if (!lst_env->line[i] && !str[i])
			return (1);
		lst_env = lst_env->next;
	}
	return (0);
}

char	*replace_line_env(char *str)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!line)
		return (error("MALLOC FALURE\n"), NULL);
	while (str[i])
	{
		line[i] = str[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

int	doublon_var(char *str, t_lst_env **lst_env)
{
	int			i;
	t_lst_env	*tmp;

	tmp = *lst_env;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i] && str[i] && tmp->line[i] != '=')
		{
			if (tmp->line[i] != str[i])
				break ;
			i++;
		}
		if (str[i] && str[i] == '=' && tmp->line[i] && tmp->line[i] == '=')
		{
			free(tmp->line);
			tmp->line = replace_line_env(str);
			if (!tmp->line)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	push_env(char *str, t_struct_data *s)
{
	int	nb;
	int	nb2;

	if (doublon_var_content(str, s->lst_env))
		return (1);
	nb = doublon_var(str, &s->lst_env);
	if (nb == 0)
		return (0);
	nb2 = search_replace_export(str, s);
	if (nb2 == 0)
		return (0);
	if (nb == -1)
	{
		if (!new_line_env(str, s))
			return (0);
	}
	if (nb == -1 && nb2 > -1)
	{
		if (!new_line_export(str, s, 1))
			return (0);
	}
	return (1);
}

void	builtin_export(t_cmd *cmd, t_struct_data *s)
{
	int	i;

	i = 1;
	if (!cmd->name[i])
		return (print_export(cmd, s->lst_export));
	if (its_option(cmd->name))
	{
		g_exit = 2;
		error_builtins(cmd, "invalid option", 2);
		return ;
	}
	while (cmd->name[i])
	{
		if (its_valid(cmd->name[i], cmd))
		{
			if (check_egal(cmd->name[i]))
			{
				if (!push_env(cmd->name[i], s))
					return ;
			}
			else if (!new_line_export(cmd->name[i], s, 0))
				return ;
		}
		i++;
	}
}
