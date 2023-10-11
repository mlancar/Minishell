#include "minishell.h"

int	update_quote(char *prompt, int i, t_struct_strdup *s)
{
	s->s_q = 0;
	s->d_q = 0;
	if ((in_quote(prompt, i, &s->s_q, &s->d_q)) == -1)
		return (0);
	if (s->s_q == 1)
		s->c = SINGLE_QUOTE;
	else if (s->d_q == 1)
		s->c = DOUBLE_QUOTE;
	return (1);
}
