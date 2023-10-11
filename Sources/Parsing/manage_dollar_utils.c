#include "minishell.h"

int	strlen_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
int	its_valid_expand(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	cmp_env(char *str, int *i, char *line, t_struct_strdup *s)
{
	int	x;
	int	j;

	(void) s;
	s->index_dollar = *i;
	x = *i + 1;
	j = 0;
	while (str[x] && line[j] && its_valid_expand(str[x]))
	{
		if (str[x] != line[j])
			return (0);
		x++;
		j++;
	}
	if (line[j] != '=')
		return (0);
	*i = x;
	return (1);
}
