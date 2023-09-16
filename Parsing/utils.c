/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:10:19 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 17:10:22 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)pointer;
	while (i < count)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (pointer);
}

int	ft_strcmp(const char *first, const char *second)
{
	size_t			i;
	unsigned char	*ufirst;
	unsigned char	*usecond;

	i = 0;
	if (!first || ! second)
		return (-1);
	ufirst = (unsigned char *)first;
	usecond = (unsigned char *)second;
	while (ufirst[i] && usecond[i] && ufirst[i] == usecond[i])
		i++;
	return (ufirst[i] - usecond[i]);
}
