/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:38 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 18:45:12 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_cmd(t_lst_arg **arg, t_lst_file **file, t_lst_cmd **cmd, int *i)
{
	t_lst_cmd	*new;

	if (!(*arg) && !(*file))
	{
		g_exit = 2;
		return (error("minishell: syntax error near unexpected token\n"), 0);
	}
	new = ft_lst_new_cmd();
	if (!new)
		return (0);
	ft_lst_add_back_cmd(new, cmd);
	*arg = NULL;
	*file = NULL;
	(*i)++;
	return (1);
}

int	check_and_new_cmd(char *prompt, t_struct_fill *s, t_lst_cmd **cmd)
{
	int	i;

	i = s->i;
	i++;
	while (prompt[i] && prompt[i] != '|')
	{
		if (prompt[i] != ' ')
			break ;
		i++;
	}
	if (prompt[i] == '|' || !prompt[i])
	{
		g_exit = 2;
		return (error("minishell: syntax error near unexpected token\n"), 0);
	}
	if (!new_cmd(&s->arg, &s->file, cmd, &s->i))
		return (0);
	while (prompt[s->i] == ' ')
		(s)->i++;
	return (1);
}

int	fill_lst(char *prompt, t_lst_cmd *cmd, t_lst_env *lst_env)
{
	t_struct_fill	s;

	ft_memset(&s, 0, sizeof(t_struct_fill));
	while (prompt[s.i])
	{
		while (its_white_space(prompt[s.i]))
			s.i++;
		if (prompt[s.i] && prompt[s.i] == '|')
		{
			if (!check_and_new_cmd(prompt, &s, &cmd))
				return (0);
		}
		if (prompt[s.i] && prompt[s.i] != '|' && !its_file(prompt[s.i]))
		{
			if (!fill_arg(prompt, &s.arg, &s.i, lst_env))
				return (0);
		}
		else if (prompt[s.i] && prompt[s.i] != '|')
			if (!fill_file(prompt, &s.file, &s.i, lst_env))
				return (0);
		s.tmp = ft_lst_last_cmd(cmd);
		s.tmp->arg = s.arg;
		s.tmp->file = s.file;
	}
	return (1);
}
