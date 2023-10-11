#include "minishell.h"

int	count_c(char *prompt, char c, int *i)
{
	int	count;

	count = 0;
	while (prompt[*i] && prompt[*i] == c)
	{
		count++;
		(*i)++;
	}
	if (count > 2)
		return (error("minishell: syntax error near unexpected token\n"), 0);
	return (1);
}

int	prep_malloc(char *prompt, t_struct_strdup *s, int *i)
{
	while (prompt[*i] && !token(prompt, *i))
	{
		if (prompt[*i] == ' ' && !in_quote(prompt, *i, &s->s_q, &s->d_q))
			break ;
		if (prompt[*i] == '$')
			if (check_dollar(prompt, i, s) == -1)
				return (0);
		if (!update_quote(prompt, *i, s))
			return (0);
		if (prompt[*i] && prompt[*i] == s->c)
			s->count++;
		else if (prompt[*i])
			s->len++;
		(*i)++;
	}
	if (s->env_type == 1)
	{
		*i = s->index_dollar;
		s->len += s->len_env;
	}
	return (1);
}

int	fill_str(char *prompt, t_struct_strdup *s, int *i)
{
	if (s->env_type == 0)
	{
		*i -= s->len;
		*i -= s->count;
	}
	while (prompt[*i] && !token(prompt, *i))
	{
		if (prompt[*i] == ' ' && !in_quote(prompt, *i, &s->s_q, &s->d_q))
			break ;
		if (prompt[*i] == '$')
			if (check_dollar(prompt, i, s) == -1)
				return (0);
		if (!update_quote(prompt, *i, s))
			return (0);
		if (prompt [*i] && prompt[*i] != s->c)
			s->str[s->j++] = prompt[*i];
		(*i)++;
	}
	s->str[s->j] = 0;
	return (1);
}

char	*dup_str(char *prompt, int *i, int nb, t_lst_env *lst_env)
{
	t_struct_strdup	s;

	ft_memset(&s, 0, sizeof(t_struct_strdup));
	s.lst_env = lst_env;
	if (nb == FILE)
		if (!count_c(prompt, prompt[*i], i))
			return (NULL);
	while (prompt[*i] && its_white_space(prompt[*i]))
		(*i)++;
	if (!prep_malloc(prompt, &s, i))
		return (0);
	s.str = malloc(sizeof(char) * s.len + 1);
	if (!s.str)
		return (error("MALLOC FAILURE\n"), NULL);
	if (!fill_str(prompt, &s, i))
		return (free(s.str), NULL);
	return (s.str);
}
