/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:03:30 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 19:18:59 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	its_oldpwd(char *str)
{
	int		i;
	char	*old_pwd;

	i = 0;
	old_pwd = "OLDPWD";
	while (str[i] && old_pwd[i] && str[i] == old_pwd[i])
		i++;
	if (str[i] && str[i] == '=' && !old_pwd[i])
		return (1);
	return (0);
}

int	its_pwd(char *str)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = "PWD";
	while (str[i] && pwd[i] && str[i] == pwd[i])
		i++;
	if (str[i] && str[i] == '=' && !pwd[i])
		return (1);
	return (0);
}
