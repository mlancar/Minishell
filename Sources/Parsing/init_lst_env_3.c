/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_env_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:23:19 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 18:10:38 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_export(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

char	*lets_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 3);
	if (!s3)
		return (error("MALLOC FAILURE\n"), NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] && s2[i] != '=')
		s3[j++] = s2[i++];
	s3[j++] = '=';
	s3[j++] = '"';
	i++;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j++] = '"';
	s3[j] = 0;
	return (s3);
}

int	join_declare_x(t_lst_env **lst_export)
{
	char		*line_tmp;
	t_lst_env	*lst_tmp;

	lst_tmp = *lst_export;
	while (lst_tmp)
	{
		line_tmp = lets_join("declare -x ", lst_tmp->line);
		if (!line_tmp)
			return (0);
		free(lst_tmp->line);
		lst_tmp->line = line_tmp;
		lst_tmp = lst_tmp->next;
	}
	return (1);
}

int	init_my_env(char **env, t_struct_data *s)
{
	if (!env[0] && !s->my_env)
	{
		s->my_env = create_env();
		if (!s->my_env)
			return (0);
	}
	else if (!s->my_env)
	{
		s->my_env = old_env(env);
		if (s->my_env == 0)
			return (0);
		if (!update_shlvl(s))
			return (0);
	}
	return (1);
}

int	check_pwd_shlvl(t_lst_env **lst_env)
{
	if (!check_fill_pwd(lst_env))
		return (0);
	if (!check_fill_shlvl(lst_env))
		return (0);
	return (1);
}
