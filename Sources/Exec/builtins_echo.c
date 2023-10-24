#include "pipex.h"

int	its_option_echo(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtins_echo(char **argv)
{
	int	i;
	int	option;
	int	arg;

	i = 1;
	option = 0;
	arg = 0;
	while (argv[i])
	{
		if (its_option_echo(argv[i]) && arg == 0)
			option = 1;
		else if (argv[i])
		{
			arg = 1;
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
		}
		i++;
	}
	if (option == 0)
		printf("\n");
	return (1);
}
