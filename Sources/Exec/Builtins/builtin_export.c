/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:32 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 18:29:06 by malancar         ###   ########.fr       */
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

char	*replace_line(char *str)
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
		if (tmp->line[i] && tmp->line[i] == '=')
		{
			free(tmp->line);
			tmp->line = replace_line(str);
			if (!tmp->line)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	push_env(char *str, t_lst_env **lst_env)
{
	int	nb;

	if (doublon_var_content(str, *lst_env))
		return (1);
	nb = doublon_var(str, lst_env);
	if (nb == 0)
		return (0);
	if (nb == 1)
		return (1);
	return (1);
}

int	builtins_export(t_cmd *cmd, t_struct_env *s)
{
	int	i;

	i = 1;
	if (!cmd->argv[i])
	{
		print_export(cmd, s->lst_export);
		return (1);
	}
	if (its_option(cmd->argv))
		return (1);
	while (cmd->argv[i])
	{
		if (its_valid(cmd->argv[i]))
		{
			if (check_egal(cmd->argv[i]))
			{
				if (!push_env(cmd->argv[i], &s->lst_env))
					return (0);
			}
			//else
			//	push_export(argv[i], &s->lst_export);
		}
		i++;
	}
	return (1);
}
