/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:15:11 by auferran          #+#    #+#             */
/*   Updated: 2023/11/21 18:10:51 by auferran         ###   ########.fr       */
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
# include <string.h>
# include <errno.h>

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define FILE 1
# define HD 2
# define IN 1
# define OUT 2

extern int	g_exit;

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

typedef struct s_struct_data
{
	char		*prompt;
	char		**my_env;
	t_lst_cmd	*cmd;
	t_lst_env	*lst_env;
	t_lst_env	*lst_export;
}				t_struct_data;

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
	int			dollar_type;
	int			file_type;
	int			index_dollar;
	int			index_file;
	int			query_prep;
	int			after_space;
	int			s_q;
	int			d_q;
	int			count;
	int			nb_fill;
	int			void_dollar;
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

void		free_parsing(t_struct_data *s);
void		free_my_env(char **my_env);
void		free_dest_env(char ***dest);

void		manage(char *prompt, t_struct_data *s);

int			manage_sig(void);

char		*ft_itoa(int n);

int			ft_strlen(char *str);
void		ft_putstr(char *str);
int			ft_isalpha(int character);
void		*ft_memset(void *pointer, int value, size_t count);
int			ft_strcmp(const char *first, const char *second);
char		*ft_strjoin_libft(char const *s1, char const *s2);
int			ft_atoi(const char *theString);

int			strlen_env(char *str);
int			cmp_env(char *str, int *i, char *line);

void		init_lst_env(char **env, t_struct_data *s);

void		sort_export(t_lst_env **lst_export);
int			join_declare_x(t_lst_env **lst_export);
int			init_my_env(char **env, t_struct_data *s);
char		**create_env(void);
char		**old_env(char **env);
void		swap_export(char **str1, char **str2);
int			update_i_dollar(char *prompt, int *i, t_struct_strdup *s);
int			update_shlvl(t_struct_data *s);
int			check_pwd_shlvl(t_lst_env **lst_env);
int			check_fill_pwd(t_lst_env **lst_env);
int			check_fill_shlvl(t_lst_env **lst_env);
int			its_shlvl(char *line);
int			its_pwd(char *str);
char		*create_pwd(void);
char		*create_shlvl(void);

int			check_prompt(char *prompt);

int			fill_lst(char *prompt, t_lst_cmd *cmd, t_lst_env *lst_env);

int			fill_arg(char *prompt, t_lst_arg **arg, int *i, t_lst_env *lst_env);

int			fill_file(char *prompt, t_lst_file **file, int *i, t_lst_env *lst_env);

char		*dup_str(char *prompt, int *i, int *nb, t_lst_env *lst_env);

t_lst_cmd	*ft_lst_new_cmd(void);
t_lst_cmd	*ft_lst_last_cmd(t_lst_cmd *cmd);
void		ft_lst_add_back_cmd(t_lst_cmd *lst_new, t_lst_cmd **lst);
int			ft_lst_size_cmd(t_lst_cmd *cmd);
void		ft_lst_clear_cmd(t_lst_cmd **cmd);

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

int			check_dollar_count(char *prompt, int *i, int file, t_struct_strdup *s);
int			check_dollar_expand(char *prompt, int *i, int file, t_struct_strdup *s);

void		dollar_query_prep(int *i, t_struct_strdup *s);
int			dollar_query_fill(int *i, t_struct_strdup *s);

void		count_env(char *line, t_struct_strdup *s);
void		expand(t_struct_strdup *s, char *line);
int			ft_isdigit(int character);
int			token(char *prompt, int i);
int			check_reverse_file(char *prompt, int i);

int			its_white_space(char c);
int			its_file(char c);

int			its_valid_expand(char c);

char		*lets_join(char *s1, char *s2);
void		sort_export(t_lst_env **lst_export);

#endif
