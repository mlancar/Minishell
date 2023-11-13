/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:53:30 by malancar          #+#    #+#             */
/*   Updated: 2023/11/13 15:24:23 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	set_oldpwd_var(t_cmd *cmd)
{
	int	pwd;
	int	oldpwd;
	int	i;
	int	j;

	pwd = get_env_line(cmd, "PWD=");
	oldpwd = get_env_line(cmd, "OLDPWD=");
	i = 4;
	j = 7;
	//free(cmd->env[oldpwd]);
	cmd->env[oldpwd] = malloc(sizeof(char) * ft_strlen(cmd->env[pwd]) + j + 1);
	if (!cmd->env[oldpwd])
		return ;
	cmd->env[oldpwd] = strcpy(cmd->env[oldpwd], "OLDPWD=");
	while (cmd->env[pwd][i])
	{
		cmd->env[oldpwd][j] = cmd->env[pwd][i];
		i++;
		j++;
	}
	cmd->env[oldpwd][j] = '\0';
	//printf("oldpwd = %s\n", cmd->env[oldpwd]);
}

void	set_pwd_var(t_cmd *cmd)
{
	int		pwd;
	char	*pwd_var;
	int		i;
	int		j;

	i = 4;
	j = 0;
	pwd = get_env_line(cmd, "PWD=");
	pwd_var = getcwd(NULL, 0);
	if (!pwd_var)
	{
		free(pwd_var);
		return ;
	}
	//free(cmd->env[oldpwd]);
	cmd->env[pwd] = malloc(sizeof(char) * ft_strlen(pwd_var) + i + 1);
	if (!cmd->env[pwd])
	{
		free(pwd_var);
		return ;
	}
	cmd->env[pwd] = strcpy(cmd->env[pwd], "PWD=");
	while (pwd_var[j])
	{
		cmd->env[pwd][i] = pwd_var[j];
		i++;
		j++;
	}
	cmd->env[pwd][i] = '\0';
	free(pwd_var);
	//printf("apres pwd = %s\n", cmd->env[pwd]);
}

int	builtin_cd(t_cmd *cmd)
{
	char	*path;
	int		i;
	int		len;

	len = 0;
	i = 0;
	path = cmd->argv[1];
	if (builtin_arg_nbr(cmd) == -1)
		return (error_builtins(cmd), 0);
	if (path == NULL)
	{
		i = get_env_line(cmd, "HOME=");
		if (i == 0)
		{
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": HOME not set\n", 2);
			return (0);
		}
		path = &cmd->env[i][5];
	}
	if (chdir(path) == -1)
		return (error_builtins(cmd), 0);
	set_oldpwd_var(cmd);
	set_pwd_var(cmd);
	return (1);
}
