/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:53:30 by malancar          #+#    #+#             */
/*   Updated: 2023/11/22 15:38:08 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

char	*find_pwd(t_lst_env *env)
{
	char	*dest;

	dest = NULL;
	while (env)
	{
		if (its_pwd(env->line))
		{
			dest = ft_strjoin_libft("OLD", env->line);
			if (!dest)
				return (NULL);
			break ;
		}
		env = env->next;
	}
	return (dest);
}

int	set_oldpwd(t_struct_data *s)
{
	char		*str_tmp;
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		if (its_oldpwd(tmp->line))
		{
			str_tmp = find_pwd(s->lst_env);
			if (!str_tmp)
				return (0);
			free(tmp->line);
			tmp->line = str_tmp;
			if (!search_replace_export(tmp->line, s))
				return (0);
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	set_pwd(t_struct_data *s)
{
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		if (its_pwd(tmp->line))
		{
			free(tmp->line);
			tmp->line = create_pwd();
			if (!tmp->line || !search_replace_export(tmp->line, s))
				return (0);
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	builtin_cd(t_cmd *cmd, t_struct_data *s)
{
	char	*path;
	int		i;

	i = 0;
	path = cmd->name[1];
	if (builtin_arg_nbr(cmd) > 2)
		return (error_builtins(cmd, "too many arguments", 1));
	if (path == NULL)
	{
		i = get_env_line(cmd, "HOME=");
		if (i == 0)
		{
			ft_putstr_fd(cmd->name[0], 2);
			ft_putstr_fd(": HOME not set\n", 2);
			return ;
		}
		path = &cmd->env[i][5];
	}
	if (chdir(path) == -1)
		return (error_builtins(cmd, NULL, 1));
	if (!set_oldpwd(s) || !set_pwd(s))
		return ;
	g_exit = 0;
}
