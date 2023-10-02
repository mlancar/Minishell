/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:02:38 by auferran          #+#    #+#             */
/*   Updated: 2023/09/30 17:21:06 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_file(char *prompt, char c, int *i)
{
	t_struct_dup_file	s;

	ft_memset(&s, 0, sizeof(t_struct_dup_file));
	while (prompt[*i] && prompt[*i] == c)
	{
		s.count++;
		(*i)++;
	}
	if (s.count > 1)
		return (error("minishell: syntax error \
			near unexpected token\n"), NULL);
	while (prompt[*i] && its_white_space(prompt[*i]))
		(*i)++;
	while (prompt[*i] && prompt[*i] != '|' && !its_white_space(prompt[*i]))
	{
		(*i)++;
		s.len++;
	}
	s.str = malloc(sizeof(char) * s.len + 1);
	if (!s.str)
		return (error("MALLOC FAILURE\n"), NULL);
	*i -= s.len;
	while (prompt[*i] && !its_white_space(prompt[*i]))
		s.str[s.j++] = prompt[(*i)++];
	s.str[s.j] = 0;
	return (s.str);
}

void	fill_file(char *prompt, t_lst_file	**file, int *i)
{
	t_lst_file	*new;

	new = malloc(sizeof(t_lst_file));
	if (!new)
		return (error("ERROR MALLOC\n"));
	ft_memset(new, 0, sizeof(t_lst_file));
	if (its_file(prompt[*i]) == INFILE && !its_file(prompt[*i + 1]))
		if ((new->infile = dup_file(prompt, prompt[*i], i)) == NULL)
			return ;
	if (its_file(prompt[*i]) == OUTFILE && !its_file(prompt[*i + 1]))
		if ((new->outfile = dup_file(prompt, prompt[*i], i)) == NULL)
			return ;
	if (its_file(prompt[*i]) == INFILE && its_file(prompt[*i + 1]) == INFILE)
		if ((new->limiter = dup_file(prompt, prompt[*i], i)) == NULL)
			return ;
	if (its_file(prompt[*i]) == OUTFILE && its_file(prompt[*i + 1]) == OUTFILE)
	{
		new->outfile_type = 1;
		if ((new->infile = dup_file(prompt, prompt[*i], i)) == NULL)
			return ;
	}
	ft_lst_add_back_file(new, file);
}

char	*dup_arg(char *prompt, int *i)
{
	t_struct_dup_arg	s;

	ft_memset(&s, 0, sizeof(t_struct_dup_arg));
	while (prompt[*i] && its_white_space(prompt[*i]))
		(i++);
	s.len = 0;
	while (prompt[*i] && prompt[*i] != '|' && !its_white_space(prompt[*i]))
	{
		s.len++;
		(*i)++;
	}
	s.str = malloc(sizeof(char) * s.len + 1);
	if (!s.str)
		return (error("MALLOC FAILURE\n"), NULL);
	s.j = 0;
	*i -= s.len;
	while (prompt[*i] && prompt[*i] != '|' && !its_white_space(prompt[*i]))
		s.str[s.j++] = prompt[(*i)++];
	s.str[s.j] = 0;
	return (s.str);
}

void	fill_arg(char *prompt, t_lst_arg **arg, int *i)
{
	t_lst_arg	*new;

	if (prompt[*i] == '|')
		return ;
	new = malloc(sizeof(t_lst_arg));
	if (!new)
		return (error("ERROR MALLOC\n"));
	ft_memset(new, 0, sizeof(t_lst_arg));
	if (ft_lst_size_arg(*arg) == 0)
		if ((new->name = dup_arg(prompt, i)) == NULL)
			return ;
	if (ft_lst_size_arg(*arg) > 0)
	{
		if ((new->arg = dup_arg(prompt, i)) == NULL)
			return ;
	}
	ft_lst_add_back_arg(new, arg);
}

int	fill_lst(char *prompt, t_lst_cmd *cmd)
{
	int			i;
	t_lst_cmd	*new;
	t_lst_cmd	*tmp;
	t_lst_arg	*arg;
	t_lst_file	*file;

	i = 0;
	new = NULL;
	tmp = NULL;
	arg = NULL;
	file = NULL;
	while (prompt[i])
	{
		if (prompt[i] == '|')
		{
			new = ft_lst_new_cmd();
			if (!new)
				return (0);
			ft_memset(new, 0, sizeof(t_lst_cmd));
			
			ft_lst_add_back_cmd(new, &cmd);
			arg = NULL;
			file = NULL;
			i++;
		}
		while (its_white_space(prompt[i]))
			i++;
		if (prompt[i] && !its_file(prompt[i]))
			fill_arg(prompt, &arg, &i);
		else if (prompt[i] && prompt[i] != '|')
			fill_file(prompt, &file, &i);
		tmp = ft_lst_last_cmd(cmd);
		tmp->arg = arg;
		tmp->file = file;
	}
	return (1);
}
