/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:24:00 by auferran          #+#    #+#             */
/*   Updated: 2023/11/23 23:05:54 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	init_lst(t_lst_cmd **cmd)
{
	t_lst_cmd	*lst_new;

	lst_new = NULL;
	lst_new = ft_lst_new_cmd();
	if (!lst_new)
		return (0);
	ft_lst_add_back_cmd(lst_new, cmd);
	return (1);
}

void	manage(char *prompt, t_struct_data *s)
{
	if (!check_prompt(prompt))
		return ;
	if (!init_lst(&s->cmd))
		return ;
	if (!fill_lst(prompt, s->cmd, s->lst_env))
		return (ft_lst_clear_cmd(&s->cmd));
	start_exec(s->cmd, s);
	ft_lst_clear_cmd(&s->cmd);
	return ;
}
