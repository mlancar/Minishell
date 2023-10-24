#include "pipex.h"

int	builtins_env(char **argv, t_lst_env *env_list)
{
	if (argv[1])
		return (0);
	while (env_list)
	{
		printf("%s\n", env_list->line);
		env_list = env_list->next;
	}
	return (1);
}
