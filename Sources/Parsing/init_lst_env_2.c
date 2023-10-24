#include "minishell.h"

void	swap_export(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

char	*lets_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 3);
	if (!s3)
		return (error("MALLOC FAILURE\n"), NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] && s2[i] != '=')
		s3[j++] = s2[i++];
	s3[j++] = '=';
	s3[j++] ='"';
	i++;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j++] = '"';
	s3[j] = 0;
	return (s3);
}

void	join_declare_x(t_lst_env **lst_export)
{
	char		*line_tmp;
	t_lst_env	*lst_tmp;

	lst_tmp = *lst_export;
	while (lst_tmp)
	{
		line_tmp = lets_join("declare -x ", lst_tmp->line);
		free(lst_tmp->line);
		lst_tmp->line = line_tmp;
		lst_tmp = lst_tmp->next;
	}
}
