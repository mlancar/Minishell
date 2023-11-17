/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:01:07 by malancar          #+#    #+#             */
/*   Updated: 2023/11/15 18:47:46 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	its_option(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1] != 0)
			return (1);
		i++;
	}
	return (0);
}

int	builtin_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(pwd);
		return (error("getcwd FAILURE\n"), 0);
	}
	ft_putstr_fd(pwd, cmd->fd.write);
	ft_putstr_fd("\n", cmd->fd.write);
	free (pwd);
	return (1);
}
