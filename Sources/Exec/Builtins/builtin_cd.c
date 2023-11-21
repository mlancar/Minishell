/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:53:30 by malancar          #+#    #+#             */
/*   Updated: 2023/11/21 17:13:32 by auferran         ###   ########.fr       */
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
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		if (its_oldpwd(tmp->line))
		{
			free(tmp->line);
			tmp->line = find_pwd(s->lst_env);
			if (!tmp->line)
				return (0);
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
	char		*pwd;
	t_lst_env	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = s->lst_env;
	if (!pwd)
	{
		free(pwd);
		return (error("getcwd FAILURE\n"), 0);
	}
	while (tmp)
	{
		if (its_pwd(tmp->line))
		{
			free(tmp->line);
			tmp->line = ft_strjoin_libft("PWD=", pwd);
			if (!tmp->line || !search_replace_export(tmp->line, s))
			{
				free(pwd);
				return (0);
			}
			break ;
		}
		tmp = tmp->next;
	}
	free(pwd);
	return (1);
}

int	builtin_cd(t_cmd *cmd, t_struct_data *s)
{
	char	*path;
	int		i;

	i = 0;
	path = cmd->name[1];
	if (builtin_arg_nbr(cmd) == -1)
		return (error_builtins(cmd), 0);
	if (path == NULL)
	{
		i = get_env_line(cmd, "HOME=");
		if (i == 0)
		{
			ft_putstr_fd(cmd->name[0], 2);
			ft_putstr_fd(": HOME not set\n", 2);
			return (0);
		}
		path = &cmd->env[i][5];
	}
	if (chdir(path) == -1)
		return (error_builtins(cmd), 0);
	if (!set_oldpwd(s))
		return (0);
	if (!set_pwd(s))
		return (0);
	return (1);
}
