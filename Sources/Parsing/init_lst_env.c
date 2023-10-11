#include "minishell.h"

char	*dup_str_env(char *env)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(env) + 1));
	if (!str)
		return (error("MALLOC FAILURE\n"), NULL);
	i = 0;
	j = 0;
	while(env[i])
	{
		str[j] = env[i];
		j++;
		i++;
	}
	str[j] = 0;
	return (str);
}

void	init_lst_env(char **env, t_lst_env **lst_env)
{
	int			i;
	t_lst_env	*new;

	i = 0;
	new = NULL;
	while (env[i])
	{
		new = ft_lst_new_env();
		if (!new)
			return ;
		if ((new->line = dup_str_env(env[i])) == NULL)
			return ;
		ft_lst_add_back_env(new, lst_env);
		i++;
	}
}
