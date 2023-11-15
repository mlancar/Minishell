/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:16:04 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 17:16:05 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_clear_file(t_lst_file **file)
{
	int			i;
	int			size;
	t_lst_file	*tmp;

	if (!(*file))
		return ;
	i = 0;
	size = ft_lst_size_file(*file);
	while (i < size)
	{
		if (!(*file))
			return ;
		if ((*file)->infile)
			free((*file)->infile);
		if ((*file)->outfile)
			free((*file)->outfile);
		if ((*file)->limiter)
			free((*file)->limiter);
		tmp = (*file)->next;
		free(*file);
		*file = tmp;
		i++;
	}
	*file = NULL;
}

void	ft_lst_clear_arg(t_lst_arg **arg)
{
	int			i;
	int			size;
	t_lst_arg	*tmp;

	if (!(*arg))
		return ;
	i = 0;
	size = ft_lst_size_arg(*arg);
	while (i < size)
	{
		if (!(*arg))
			return ;
		if ((*arg)->name)
			free((*arg)->name);
		if ((*arg)->arg)
			free((*arg)->arg);
		tmp = (*arg)->next;
		free(*arg);
		*arg = tmp;
		i++;
	}
	*arg = NULL;
}

void	ft_lst_clear_cmd(t_lst_cmd **cmd)
{
	int			i;
	int			size;
	t_lst_cmd	*tmp;

	if (!(*cmd))
		return ;
	i = 0;
	size = ft_lst_size_cmd(*cmd);
	while (i < size)
	{
		if (!(*cmd))
			return ;
		ft_lst_clear_arg(&(*cmd)->arg);
		ft_lst_clear_file(&(*cmd)->file);
		tmp = (*cmd)->next;
		free(*cmd);
		*cmd = tmp;
		i++;
	}
	*cmd = NULL;
}

void	free_all(t_lst_cmd **cmd)
{
	ft_lst_clear_cmd(cmd);
}
