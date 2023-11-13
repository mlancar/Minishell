#include "exec.h"
#include "minishell.h"

int	doublon_var_content(char *str, t_lst_env *lst_env)
{
	int	i;

	while (lst_env)
	{
		i = 0;
		while (lst_env->line[i] && str[i])
		{
			if (lst_env->line[i] != str[i])
				break ;
			i++;
		}
		if (!lst_env->line[i] && !str[i])
			return (1);
		lst_env = lst_env->next;
	}
	return (0);
}

char	*replace_line_env(char *str)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!line)
		return (error("MALLOC FALURE\n"), NULL);
	while (str[i])
	{
		line[i] = str[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

int	doublon_var(char *str, t_lst_env **lst_env)
{
	int			i;
	t_lst_env	*tmp;

	tmp = *lst_env;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i] && str[i] && tmp->line[i] != '=')
		{
			if (tmp->line[i] != str[i])
				break ;
			i++;
		}
		if (tmp->line[i] && tmp->line[i] == '=')
		{
			free(tmp->line);
			tmp->line = replace_line_env(str);
			if (!tmp->line)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int	push_env(char *str, t_struct_env *s)
{
	int	nb;

	if (doublon_var_content(str, s->lst_env))
		return (1);
	nb = doublon_var(str, &s->lst_env);
	if (nb == 0)
		return (0);
	if (nb == 1 || nb == -1)
	{
		if (nb == 1)
		{
			if (!search_replace_export(str, s))
				return (0);
		}
		else if (nb == -1)
		{
			if (!new_line_env(str, s) || !new_line_export(str, s, 1))
			return (0);
		}
		return (1);
	}
	return (1);
}

int	builtin_export(t_cmd *cmd, t_struct_env *s)
{
	int	i;

	i = 1;
	if (!cmd->argv[i])
	{
		print_export(cmd, s->lst_export);
		return (1);
	}
	if (its_option(cmd->argv))
		return (1);
	while (cmd->argv[i])
	{
		if (its_valid(cmd->argv[i]))
		{
			if (check_egal(cmd->argv[i]))
			{
				if (!push_env(cmd->argv[i], s))
					return (0);
			}
			else if (!new_line_export(cmd->argv[i], s, 0))
				return (0);
		}
		i++;
	}
	return (1);
}
