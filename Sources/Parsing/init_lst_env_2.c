/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst_env_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:23:13 by auferran          #+#    #+#             */
/*   Updated: 2023/11/18 17:23:13 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_pwd(void)
{
	char	*pre_pwd;
	char	*pwd;
	char	*join;

	pre_pwd = "PWD=";
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free (pwd);
		return (error("getcwd FAILURE\n"), NULL);
	}
	join = ft_strjoin_libft(pre_pwd, pwd);
	if (!join)
		return (NULL);
	free (pwd);
	return (join);
}

char	*create_shlvl(void)
{
	int		i;
	char	*shlvl;
	char	*dest;

	shlvl = "SHLVL=1";
	dest = malloc(sizeof(char) * ft_strlen(shlvl) + 1);
	if (!dest)
		return (error("MALLOC FAILURE\n"), NULL);
	i = 0;
	while (shlvl[i])
	{
		dest[i] = shlvl[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**create_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 2 + 1);
	if (!env)
		return (NULL);
	env[0] = create_pwd();
	if (!env[0])
		return (free(env), NULL);
	env[1] = create_shlvl();
	if (!env[1])
		return (free(env[0]), free(env), NULL);
	env[2] = 0;
	return (env);
}

char	*line_env(char *line)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!dest)
		return (error("MALLOC FAILURE\n"), NULL);
	while (line[i])
	{
		dest[i] = line[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**old_env(char **env)
{
	int		i;
	char	**dest;

	i = 0;
	while (env[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (error("MALLOC FAILURE\n"), NULL);
	i = 0;
	while (env[i])
	{
		dest[i] = line_env(env[i]);
		if (!dest[i])
			return (free_dest_env(&dest), NULL);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
