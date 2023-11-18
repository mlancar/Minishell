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

#include "exec.h"

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

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == 5)
		return (0);
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

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_bzero(tab, size * nmemb);
	return (tab);
}
