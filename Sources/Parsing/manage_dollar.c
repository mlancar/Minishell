#include "minishell.h"

void	count_env(char *line, t_struct_strdup *s)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		s->len_env++;
		i++;
	}
	s->env_type = 1;
}

void	expand(t_struct_strdup *s, char *line)
{
	int	i;

	i = strlen_env(line) + 1;
	while (line[i])
	{
		s->str[s->j] = line[i];
		s->j++;
		i++;
	}
	s->env_type = 0;
}

int	search_and_count_env(char *prompt, int *i, t_struct_strdup *s)
{
	while (s->lst_env)
	{
		if (cmp_env(prompt, i, s->lst_env->line, s))
		{
			if (s->env_type == 0)
				count_env(s->lst_env->line, s);
			else if (s->env_type == 1)
				expand(s, s->lst_env->line);
			return (1);
		}
		s->lst_env = s->lst_env->next;
	}
	return (0);
}

int	check_dollar(char *prompt, int *i, t_struct_strdup *s)
{
	if (prompt[*i] == '$' && !its_valid_expand(prompt[*i + 1]))
		return (0);
	if (in_quote(prompt, *i, &s->s_q, &s->d_q) && s->s_q == 1)
		return (0) ;
	else if (!search_and_count_env(prompt, i, s))
		return (-1) ;
	return (1);
}
