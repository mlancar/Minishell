/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:15:11 by auferran          #+#    #+#             */
/*   Updated: 2023/09/16 17:15:15 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR_MALLOC 0
# define ERROR_PROMPT 1

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env_pipex
{
	char		*cmd;
	t_lst_arg	*arg;
	t_lst_hd	*heredoc;
	t_lst_files	*file;
	t_env_pipex	*next;
}				t_env_pipex;

typedef struct s_lst_arg
{
	char		*arg;
	s_lst_arg	*next;
}				t_lst_arg;

typedef struct s_lst_hd
{
	char		*limiter;
	s_lst_hd	*next;
}				t_lst_hd;

typedef struct s_lst_file
{
	char		*infile;
	char		*outfile;
	t_lst_file	*next;
}				t_lst_file;

void	error(int nb);
void	free_all(char **prompt, s_env_pipex **env_pipex);
void	minishell(char **env);
int		manage_sig(void);
int		ft_strcmp(const char *first, const char *second);
void	*ft_memset(void *pointer, int value, size_t count);
int		init_struct(char *prompt, s_env_pipex **env_pipex);
int		check_prompt(char *prompt, s_env_pipex *env_pipex);

#endif
