#include "minishell.h"

void	dollar_query_prep(int *i, t_struct_strdup *s)
{
	int	nb;

	(void) i;
	nb = g_exit;
	while (nb > 10)
	{
		nb = nb / 10;
		s->len++;
	}
	s->len += 1;
	s->dollar_type = 1;
	*i += 1;
}
int	dollar_query_fill(int *i, t_struct_strdup *s)
{
	int		x;
	char	*number;

	(void) i;
	x = 0;
	number = ft_itoa(g_exit);
	if (!number)
		return (0);
	while (number[x])
	{
		s->str[s->j] = number[x];
		s->j++;
		x++;
	}
	free(number);
	*i += 1;
	return (1);
}

