#include "pipex.h"
#include "minishell.h"

int	its_option(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1] != 0)
			return (1);
		i++;
	}
	return (0);
}

int	builtins_pwd(char **argv)
{
	char	*pwd;

	if (its_option(argv))
		return (0);
	pwd = malloc (sizeof(char) * 2048);
	if (!pwd)
		return (error("MALLOC FAILURE\n"), 0);
	if (!getcwd(pwd, 2048))
	{
		free(pwd);
		return (error("getcwd FAILURE\n"), 0);
	}
	printf("%s\n", pwd);
	free (pwd);
	return (1);
}
