/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:24:00 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 19:50:25 by auferran         ###   ########.fr       */
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

void	test_pipex(t_lst_cmd *cmd, t_lst_env *lst_env)
{
	int	i;
	int	y;
	int	x;

	(void) lst_env;
	i = 1;
	y = 1;
	x = 1;
	while (cmd != NULL)
	{
		printf("_______________________\n");
		printf("Maillon numero %d cmd\n\n", i);
		while (cmd->arg != NULL)
		{
			printf("Maillon numero %d arg\n\n", y);
			printf("name = %s\n", cmd->arg->name);
			printf("arg = %s\n", cmd->arg->arg);
			cmd->arg = cmd->arg->next;
			y++;
		}
		while (cmd->file != NULL)
		{
			printf("Maillon numero %d file\n\n", x);
			printf("infile = %s\n", cmd->file->infile);
			printf("outfile = %s\n", cmd->file->outfile);
			printf("outfile_type = %d\n", cmd->file->outfile_type);
			printf("limiter = %s\n", cmd->file->limiter);
			cmd->file = cmd->file->next;
			x++;
		}
		cmd = cmd->next;
		i++;
		y = 1;
		x = 1;
	}
}

void	manage(char *prompt, t_struct_data *s)
{
	if (!check_prompt(prompt))
		return ;
	if (!init_lst(&s->cmd))
		return ;
	if (!fill_lst(prompt, s->cmd, s->lst_env))
		return (ft_lst_clear_cmd(&s->cmd));
	//test_pipex(s->cmd, s->lst_env);
	start_exec(s->cmd, s);
	ft_lst_clear_cmd(&s->cmd);
	return ;
}
