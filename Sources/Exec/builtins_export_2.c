#include "pipex.h"
#include "minishell.h"

void	print_export(t_lst_env *lst_export)
{
	while (lst_export)
	{
		printf("%s\n", lst_export->line);
		lst_export = lst_export->next;
	}
}

int	its_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	check_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
