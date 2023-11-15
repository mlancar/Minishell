#include "exec.h"
#include "minishell.h"

int	search_content_export(char *str, t_struct_data *s)
{
	int			i;
	int			j;
	t_lst_env	*tmp;

	tmp = s->lst_export;
	while (tmp)
	{
		i = 0;
		j = 11;
		while (str[i] && tmp->line[j] &&
		tmp->line[j] != '=' && str[i] == tmp->line[j])
		{
			i++;
			j++;
		}
		if (!str[i] && tmp->line[j] && tmp->line[j] == '=')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	search_replace_export(char *str, t_struct_data *s)
{
	int			i;
	int			j;
	t_lst_env	*tmp;

	tmp = s->lst_export;
	while (tmp)
	{
		i = 0;
		j = 11;
		while (str[i] && tmp->line[j] && str[i] != '=' &&
		tmp->line[j] != '=' && str[i] == tmp->line[j])
		{
			i++;
			j++;
		}
		if (str[i] && tmp->line[j] && str[i] == '=' && tmp->line[j] == '=')
		{
			free(tmp->line);
			tmp->line = lets_join("declare -x ", str);
			if (!tmp->line)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*lets_join_no_egal(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (error("MALLOC FAILURE\n"), NULL);
	while (s1[i])
	{
		s3[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s3[j] = s2[i];
		j++;
		i++;
	}
	s3[j] = 0;
	return (s3);
}

int	new_line_export(char *str, t_struct_data *s, int nb)
{
	t_lst_env	*new;

	if (!search_content_export(str, s))
		return (0);
	new = ft_lst_new_env();
	if (!new)
		return (0);
	if (nb == 0)
	{
		new->line = lets_join_no_egal("declare -x ", str);
		if (!new->line)
			return (0);
	}
	if (nb == 1)
	{
		new->line = lets_join("declare -x ", str);
		if (!new->line)
			return (0);
	}
	ft_lst_add_back_env(new, &s->lst_export);
	sort_export(&s->lst_export);
	return (1);
}

int	new_line_env(char *str, t_struct_data *s)
{
	int			i;
	t_lst_env	*new;

	new = ft_lst_new_env();
	if (!new)
		return (0);
	new->line = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new->line)
		return (error("MALLOC FAILURE\n"), 0);
	i = 0;
	while (str[i])
	{
		new->line[i] = str[i];
		i++;
	}
	new->line[i] = 0;
	ft_lst_add_back_env(new, &s->lst_env);
	return (1);
}
