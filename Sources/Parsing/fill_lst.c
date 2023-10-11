/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:38 by auferran          #+#    #+#             */
/*   Updated: 2023/10/03 17:14:53 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_cmd(t_lst_arg **arg, t_lst_file **file, t_lst_cmd **cmd, int *i)
{
	t_lst_cmd	*new;

	if (!(*arg) && !(*file))
		return (error("minishell: syntax error near unexpected token\n"), 0);
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
	if (prompt[i] == '|')
		return (error("minishell: syntax error near unexpected token\n"), 0);
	if (!new_cmd(&s->arg, &s->file, cmd, &s->i))
				return (0);
	return (1);
}

int	fill_file(char *prompt, t_lst_file	**file, int *i, t_lst_env *lst_env)
{
	t_lst_file	*new;

	new = ft_lst_new_file();
	if (!new)
		return (0);
	if (its_file(prompt[*i]) == INFILE && !its_file(prompt[*i + 1]))
		if ((new->infile = dup_str(prompt, i, FILE, lst_env)) == NULL)
			return (ft_lst_clear_file(&new), 0);
	if (its_file(prompt[*i]) == OUTFILE && !its_file(prompt[*i + 1]))
		if ((new->outfile = dup_str(prompt, i, FILE, lst_env)) == NULL)
			return (ft_lst_clear_file(&new), 0);
	if (its_file(prompt[*i]) == INFILE && its_file(prompt[*i + 1]) == INFILE)
		if ((new->limiter = dup_str(prompt, i, FILE, lst_env)) == NULL)
			return (ft_lst_clear_file(&new), 0);
	if (its_file(prompt[*i]) == OUTFILE && its_file(prompt[*i + 1]) == OUTFILE)
	{
		new->outfile_type = 1;
		if ((new->infile = dup_str(prompt, i, FILE, lst_env)) == NULL)
			return (ft_lst_clear_file(&new), 0);
	}
	ft_lst_add_back_file(new, file);
	return (1);
}

int	fill_arg(char *prompt, t_lst_arg **arg, int *i, t_lst_env *lst_env)
{
	t_lst_arg	*new;

	new = ft_lst_new_arg();
	if (!new)
		return (0);
	if (ft_lst_size_arg(*arg) == 0)
		if ((new->name = dup_str(prompt, i, 0, lst_env)) == NULL)
			return (ft_lst_clear_arg(&new), 0);
	if (ft_lst_size_arg(*arg) > 0)
	{
		if ((new->arg = dup_str(prompt, i, 0, lst_env)) == NULL)
			return (ft_lst_clear_arg(&new), 0);
	}
	ft_lst_add_back_arg(new, arg);
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
			if (!check_and_new_cmd(prompt, &s, &cmd))
				return (0);
		if (prompt[s.i] && prompt[s.i] != '|' && !its_file(prompt[s.i]))
		{
			if (!fill_arg(prompt, &s.arg, &s.i, lst_env))
				return (ft_lst_clear_arg(&s.arg), 0);
		}
		else if (prompt[s.i] && prompt[s.i] != '|')
			if (!fill_file(prompt, &s.file, &s.i, lst_env))
				return (ft_lst_clear_file(&s.file), 0);
		s.tmp = ft_lst_last_cmd(cmd);
		s.tmp->arg = s.arg;
		s.tmp->file = s.file;
	}
	return (1);
}
