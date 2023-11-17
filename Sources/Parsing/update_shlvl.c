#include "minishell.h"

char	*init_number(char *line)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		j++;
		i++;
	}
	dest = malloc(sizeof(char) * (j + 1));
	if (!dest)
		return (error("MALLOC FAILURE\n"), NULL);
	i = i - j;
	j = 0;
	while (line[i])
		dest[j++] = line[i++];
	dest[j] = 0;
	return (dest);
}

int	update_value_shlvl(char **line)
{
	int		nb;
	char	*number;

	number = init_number(*line);
	if (!number)
		return (0);
	nb = ft_atoi((const char *)number);
	nb++;
	if (nb < 0 || nb == 1000)
		nb = 1;
	free(number);
	number = ft_itoa(nb);
	if (!number)
		return (0);
	free(*line);
	*line = ft_strjoin_libft("SHLVL=", number);
	if (!*line)
		return (free(number), 0);
	return (free(number), 1);
}

int	its_shlvl(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = "SHLVL";
	while (line[i] && str[i] && line[i] == str[i])
		i++;
	if (line[i] == '=' && !str[i])
		return (1);
	return (0);
}

int	update_shlvl(t_struct_data *s)
{
	int	i;

	i = 0;
	while (s->my_env[i])
	{
		if (its_shlvl(s->my_env[i]))
		{
			if (!update_value_shlvl(&s->my_env[i]))
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}
