/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:38 by auferran          #+#    #+#             */
/*   Updated: 2023/10/05 14:49:39 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_file(char *prompt, t_lst_file	**file, int *i)
{
	t_lst_file	*new;

	new = ft_lst_new_file();
	if (!new)
		return (0);
	if (its_file(prompt[*i]) == INFILE && !its_file(prompt[*i + 1]))
		if ((new->infile = dup_str(prompt, prompt[*i], i, FILE)) == NULL)
			return (0);
	if (its_file(prompt[*i]) == OUTFILE && !its_file(prompt[*i + 1]))
		if ((new->outfile = dup_str(prompt, prompt[*i], i, FILE)) == NULL)
			return (0);
	if (its_file(prompt[*i]) == INFILE && its_file(prompt[*i + 1]) == INFILE)
		if ((new->limiter = dup_str(prompt, prompt[*i], i, FILE)) == NULL)
			return (0);
	if (its_file(prompt[*i]) == OUTFILE && its_file(prompt[*i + 1]) == OUTFILE)
	{
		new->outfile_type = 1;
		if ((new->infile = dup_str(prompt, prompt[*i], i, FILE)) == NULL)
			return (0);
	}
	ft_lst_add_back_file(new, file);
	return (1);
}

int	fill_info(char *prompt, t_lst_info **info, int *i)
{
	t_lst_info	*new;

	new = ft_lst_new_info();
	if (!new)
		return (0);
	if (ft_lst_size_info(*info) == 0)
		if ((new->name = dup_str(prompt, prompt[*i], i, 0)) == NULL)
			return (0);
	if (ft_lst_size_info(*info) > 0)
	{
		if ((new->arg = dup_str(prompt, prompt[*i], i, 0)) == NULL)
			return (0);
	}
	ft_lst_add_back_info(new, info);
	return (1);
}

int	new_argv(t_lst_info **info, t_lst_file **file, t_lst_argv **argv, int *i)
{
	t_lst_argv	*new;

	if (!(*info) && !(*file))
		return (error("minishell: syntax error near unexpected token\n"), 0);
	new = ft_lst_new_argv();
	if (!new)
		return (0);
	ft_lst_add_back_argv(new, argv);
	*info = NULL;
	*file = NULL;
	(*i)++;
	return (1);
}

int	fill_lst(char *prompt, t_lst_argv *argv)
{
	t_struct_fill	s;

	ft_memset(&s, 0, sizeof(t_struct_fill));
	while (prompt[s.i])
	{
		while (its_white_space(prompt[s.i]))
			s.i++;
		if (prompt[s.i] == '|')
			if (!new_argv(&s.info, &s.file, &argv, &s.i))
				return (0);
		if (prompt[s.i] && prompt[s.i] != '|' && !its_file(prompt[s.i]))
		{
			if (!fill_info(prompt, &s.info, &s.i))
				return (0);
		}
		else if (prompt[s.i] && prompt[s.i] != '|')
			if (!fill_file(prompt, &s.file, &s.i))
				return (0);
		s.tmp = ft_lst_last_argv(argv);
		s.tmp->info = s.info;
		s.tmp->file = s.file;
	}
	return (1);
}
