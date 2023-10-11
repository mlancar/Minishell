#include "minishell.h"

int	token(char *prompt, int i)
{
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	if (prompt[i] == '<' && !in_quote(prompt, i, &s_q, &d_q))
		return (1);
	else if (prompt[i] == '>' && !in_quote(prompt, i, &s_q, &d_q))
		return (1);
	else if (prompt[i] == '|' && !in_quote(prompt, i, &s_q, &d_q))
		return (1);
	return (0);
}
