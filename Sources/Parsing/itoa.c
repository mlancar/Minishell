#include "minishell.h"

static void	nb_recurs(long long int nb, int size, char *dest)
{
	size -= 1;
	if (nb >= 10)
		nb_recurs(nb / 10, size, dest);
	dest[size] = nb % 10 + 48;
}

static void	nb_size(long long int nb, int *size)
{
	if (nb == 0)
		*size = 1;
	while (nb)
	{
		(*size)++;
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	long long int	nb;
	int				size;
	int				negate;
	char			*dest;

	nb = n;
	negate = 0;
	size = 0;
	if (nb < 0)
	{
		size++;
		negate = 1;
		nb = nb * -1;
	}
	nb_size(nb, &size);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (error("MALLOC FAILURE\n"), NULL);
	nb_recurs(nb, size, dest);
	if (nb == 0)
		dest[0] = '0';
	if (negate == 1)
		dest[0] = '-';
	dest[size] = '\0';
	return (dest);
}
