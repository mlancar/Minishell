/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:15:11 by auferran          #+#    #+#             */
/*   Updated: 2023/09/29 15:17:44 by malancar         ###   ########.fr       */
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


# define SINGLE_QUOTE 0
# define DOUBLE_QUOTE 1
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

typedef struct s_struct_quote
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	x_s;
	int	x_d;
}				t_struct_quote;

typedef struct s_struct_dup_arg
{
	int		j;
	int		len;
	char	*str;
}				t_struct_dup_arg;

typedef struct s_struct_dup_file
{
	int		j;
	int		count;
	int		len;
	char	*str;
}				t_struct_dup_file;

void		error(char *str);

void		free_all(char **prompt, t_lst_cmd **cmd);

void		minishell(char **env);
int			manage_sig(void);

int			ft_strlen(char *str);
void		*ft_memset(void *pointer, int value, size_t count);
int			ft_strcmp(const char *first, const char *second);

int			check_prompt(char *prompt, t_lst_cmd *cmd);
int			fill_lst(char *prompt, t_lst_cmd *cmd);

t_lst_cmd	*ft_lst_new_cmd(void);
t_lst_cmd	*ft_lst_last_cmd(t_lst_cmd *cmd);
void		ft_lst_add_back_cmd(t_lst_cmd *lst_new, t_lst_cmd **lst);\
void		ft_lst_add_back_arg(t_lst_arg *arg_new, t_lst_arg **arg);
void		ft_lst_add_back_file(t_lst_file *file_new, t_lst_file **file);
void		ft_lst_clear_cmd(t_lst_cmd **cmd);
void		ft_lst_clear_arg(t_lst_arg **arg);
void		ft_lst_clear_file(t_lst_file **file);
int			ft_lst_size_arg(t_lst_arg *arg);

int			in_quote(char *str, int c, int *in_s_quote, int *in_d_quote);
int			count_quote(char *str, int nb);

int			its_white_space(char c);
int			its_file(char c);

#endif
