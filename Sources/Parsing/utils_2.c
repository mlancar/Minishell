#include "minishell.h"

char	*ft_strjoin_libft(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (error("MALLOC FAILURE\n"), NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

int	ft_atoi(const char *theString)
{
	int	i;
	int	signe;
	int	nb;

	signe = 0;
	i = 0;
	nb = 0;
	while ((theString[i] && (theString[i] >= '\t' && theString[i] <= '\r'))
		|| (theString[i] == ' '))
		i++;
	if ((theString[i] && theString[i] == '-') || theString[i] == '+')
	{
		if (theString[i] == '-')
			signe = 1;
		i++;
	}
	while (theString[i] && theString[i] >= '0' && theString[i] <= '9')
	{
		nb = nb * 10 + (theString[i] - 48);
		i++;
	}
	if (signe == 1)
		nb = nb * -1;
	return (nb);
}
