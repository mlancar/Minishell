/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:21:00 by malancar          #+#    #+#             */
/*   Updated: 2023/10/05 14:38:55 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp_cmd(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	//printf("s1 = %s s2 = %s\n", s1, s2);
	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]) && i <= n)
	{
		//printf("s1 = %c s2 = %c i = %d\n", s1[i], s2[i], i);
		//printf("la i = %d\n", i);
		i++;
	}
	//printf("ici i = %d\n", i);
	//printf("%d\n", s1[i] - s2[i]);
	if (i == 5)
		return (0);
	//printf("%c - %c = %d\n", s1[i], s2[i], s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

int	list_size(t_lst_cmd *list)
{
	int			size;

	if (!list)
		return (0);
	size = 0;
	while (list != NULL)
	{
		list = list->next;
		size++;
	}
	return (size);
}