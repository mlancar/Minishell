#include "exec.h"
#include "minishell.h"

int	valid_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_link(t_lst_env **lst_env, t_lst_env **link)
{
	t_lst_env	*tmp;

	tmp = *lst_env;
	if (tmp == *link)
	{
		*lst_env = (*lst_env)->next;
		free(tmp->line);
		free(tmp);
		return ;
	}
	while (tmp->next)
	{
		if (tmp->next == *link)
		{
			tmp->next = (*link)->next;
			free((*link)->line);
			free(*link);
			return ;
		}
		tmp = tmp->next;
	}
}

void	lets_unset_env(char *str, t_struct_env *s)
{
	int			i;
	t_lst_env	*tmp;

	tmp = s->lst_env;
	while (tmp)
	{
		i = 0;
		while (str[i] && tmp->line[i] && tmp->line[i] != '='
		&& str[i] == tmp->line[i])
			i++;
		if (!str[i] && tmp->line[i] == '=')
		{
			free_link(&s->lst_env, &tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void	lets_unset_export(char *str, t_struct_env *s)
{
	int			i;
	int			j;
	t_lst_env	*tmp;

	tmp = s->lst_export;
	while (tmp)
	{
		i = 0;
		j = 11;
		while (str[i] && tmp->line[j] && tmp->line[j] != '='
		&& str[i] == tmp->line[j])
		{
			i++;
			j++;
		}
		if (!str[i] && tmp->line[j] == '=')
		{
			free_link(&s->lst_export, &tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_struct_env *s)
{
	int	i;

	if (its_option(cmd->argv))
		return (1);
	i = 1;
	while (cmd->argv[i])
	{
		if (valid_unset(cmd->argv[i]))
		{
			lets_unset_env(cmd->argv[i], s);
			lets_unset_export(cmd->argv[i], s);
		}
		i++;
	}
	return (1);
}
