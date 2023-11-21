/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:53:23 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 20:10:32 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_hd(char *prompt, t_lst_file **file, int *i, t_lst_env *lst_env)
{
	int			nb;
	t_lst_file	*new;

	new = ft_lst_new_file();
	if (!new)
		return (0);
	nb = HD;
	new->limiter = dup_str(prompt, i, &nb, lst_env);
	if (!new->limiter)
		return (ft_lst_clear_file(&new), 0);
	if (nb == -1 && !ft_strlen(new->limiter))
	{
		free(new->limiter);
		new->limiter = NULL;
	}
	ft_lst_add_back_file(new, file);
	return (1);
}

int	fill_outfile_2(char *prompt, t_lst_file **file, int *i, t_lst_env *lst_env)
{
	int			nb;
	t_lst_file	*new;

	new = ft_lst_new_file();
	if (!new)
		return (0);
	nb = FILE;
	new->outfile_type = 1;
	new->outfile = dup_str(prompt, i, &nb, lst_env);
	if (!new->outfile)
		return (ft_lst_clear_file(&new), 0);
	if (nb == -1 && !ft_strlen(new->outfile))
	{
		free(new->outfile);
		new->outfile = NULL;
	}
	ft_lst_add_back_file(new, file);
	return (1);
}

int	fill_outfile(char *prompt, t_lst_file **file, int *i, t_lst_env *lst_env)
{
	int			nb;
	t_lst_file	*new;

	new = ft_lst_new_file();
	if (!new)
		return (0);
	nb = FILE;
	new->outfile = dup_str(prompt, i, &nb, lst_env);
	if (!new->outfile)
		return (ft_lst_clear_file(&new), 0);
	if (nb == -1 && !ft_strlen(new->outfile))
	{
		free(new->outfile);
		new->outfile = NULL;
	}
	ft_lst_add_back_file(new, file);
	return (1);
}

int	fill_infile(char *prompt, t_lst_file **file, int *i, t_lst_env *lst_env)
{
	int			nb;
	t_lst_file	*new;

	new = ft_lst_new_file();
	if (!new)
		return (0);
	nb = FILE;
	new->infile = dup_str(prompt, i, &nb, lst_env);
	if (!new->infile)
		return (ft_lst_clear_file(&new), 0);
	if (nb == -1 && !ft_strlen(new->infile))
	{
		free(new->infile);
		new->infile = NULL;
	}
	ft_lst_add_back_file(new, file);
	return (1);
}

int	fill_file(char *p, t_lst_file **file, int *i, t_lst_env *lst_env)
{
	if (!check_reverse_file(p, *i))
		return (0);
	if (its_file(p[*i]) == IN && !its_file(p[*i + 1]))
	{
		if (!fill_infile(p, file, i, lst_env))
			return (0);
	}
	else if (its_file(p[*i]) == OUT && !its_file(p[*i + 1]))
	{
		if (!fill_outfile(p, file, i, lst_env))
			return (0);
	}
	else if ((its_file(p[*i]) == IN && its_file(p[*i + 1]) == IN))
	{
		if (!fill_hd(p, file, i, lst_env))
			return (0);
	}
	else if (its_file(p[*i]) == OUT && its_file(p[*i + 1]) == OUT)
	{
		if (!fill_outfile_2(p, file, i, lst_env))
			return (0);
	}
	return (1);
}
