/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:15:11 by auferran          #+#    #+#             */
/*   Updated: 2023/10/11 15:10:54 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define FILE 1
# define INFILE 1
# define OUTFILE 2

typedef struct s_lst_arg
{
	char				*name;
	char				*arg;
	struct s_lst_arg	*next;
}						t_lst_arg;

typedef struct s_lst_file
{
	char				*infile;
	char				*outfile;
	int					outfile_type;
	char				*limiter;
	struct s_lst_file	*next;
}						t_lst_file;

typedef struct s_lst_cmd
{
	struct s_lst_arg	*arg;
	struct s_lst_file	*file;
	struct s_lst_cmd	*next;
}						t_lst_cmd;

typedef struct s_lst_env
{
	char				*line;
	struct s_lst_env	*next;
}						t_lst_env;

typedef struct s_struct_quote
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	x_s;
	int	x_d;
}				t_struct_quote;

typedef struct s_struct_strdup
{
	int			j;
	int			len;
	int			len_env;
	int			index_dollar;
	int			env_type;
	int			s_q;
	int			d_q;
	int			count;
	char		c;
	char		*str;
	t_lst_env	*lst_env;
}				t_struct_strdup;

typedef struct s_struct_fill
{
	int			i;
	int			s_q;
	int			d_q;
	t_lst_cmd	*tmp;
	t_lst_arg	*arg;
	t_lst_file	*file;
}				t_struct_fill;


void		error(char *str);

void		free_all(t_lst_cmd **cmd);

void		manage(char *prompt, char **env, t_lst_env **lst_env);

int			manage_sig(void);

int			ft_strlen(char *str);
void		*ft_memset(void *pointer, int value, size_t count);
int			ft_strcmp(const char *first, const char *second);

int			strlen_env(char *str);
int			cmp_env(char *first, int *i, char *second, t_struct_strdup *s);

void		init_lst_env(char **env, t_lst_env **lst_env);

int			check_prompt(char *prompt, t_lst_cmd *cmd);

int			fill_lst(char *prompt, t_lst_cmd *cmd, t_lst_env *lst_env);

char		*dup_str(char *prompt, int *i, int nb, t_lst_env *lst_env);

t_lst_cmd	*ft_lst_new_cmd(void);
t_lst_cmd	*ft_lst_last_cmd(t_lst_cmd *cmd);
void		ft_lst_add_back_cmd(t_lst_cmd *lst_new, t_lst_cmd **lst);
int			ft_lst_size_cmd(t_lst_cmd *cmd);

t_lst_arg	*ft_lst_new_arg(void);
void		ft_lst_add_back_arg(t_lst_arg *arg_new, t_lst_arg **arg);
int			ft_lst_size_arg(t_lst_arg *arg);
void		ft_lst_clear_arg(t_lst_arg **arg);

t_lst_file	*ft_lst_new_file(void);
void		ft_lst_add_back_file(t_lst_file *file_new, t_lst_file **file);
int			ft_lst_size_file(t_lst_file *file);
void		ft_lst_clear_file(t_lst_file **file);

t_lst_env	*ft_lst_new_env(void);
void		ft_lst_add_back_env(t_lst_env *env_new, t_lst_env **lst_env);
void		ft_lst_clear_env(t_lst_env **lst_env);

int			in_quote(char *str, int c, int *in_s_quote, int *in_d_quote);
int			update_quote(char *prompt, int i, t_struct_strdup *s);

int			check_dollar(char *prompt, int *i, t_struct_strdup *s);

int			token(char *prompt, int i);

int			its_white_space(char c);
int			its_file(char c);

int			its_valid_expand(char c);

#endif
