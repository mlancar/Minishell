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

void	fill_lst_env(char **env, t_lst_env	**lst_env)
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

int	is_sort(t_lst_env *export)
{
	int	i;

	while (export)
	{
		i = 0;
		while (export->line && export->line[i] &&
		 export->next && export->next->line[i])
		{
			if (export->line[i] < export->next->line[i])
				break ;
			else if (export->line[i] > export->next->line[i])
				return (0);
			i++;
		}
		export = export->next;
	}
	return (1);
}

void	sort_export(t_lst_env **lst_export)
{
	int			i;
	t_lst_env	*tmp;

	tmp = *lst_export;
	while (!is_sort(*lst_export))
	{
		while (tmp)
		{
			i = 0;
			while (tmp->line && tmp->line[i] && tmp->next
			&& tmp->next->line[i])
			{
				if (tmp->line[i] < tmp->next->line[i])
					break ;
				else if (tmp->line[i] > tmp->next->line[i])
				{
					swap_export(&tmp->line, &tmp->next->line);
					break;
				}
				i++;
			}
		tmp = tmp->next;
		}
	tmp = *lst_export;
	}
}

void	init_lst_env(char **env, t_struct_env *s)
{
	if (!env)
		return ;
	fill_lst_env(env, &s->lst_env);
	fill_lst_env(env, &s->lst_export);
	sort_export(&s->lst_export);
	join_declare_x(&s->lst_export);
}
