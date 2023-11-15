/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/11/07 13:58:03 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>
# include "../Sources/Exec/Get_next_line/get_next_line.h"
# include "minishell.h"

typedef struct s_files {
	int		here_doc;
	char	rand_name[7];
	int		line;
}	t_files;

typedef	struct s_fd {
	int	read;
	int	write;
	int	other_pipe;
	int	previous;
	int	tmp;
	int	pipe[2];
}	t_fd;

typedef struct s_cmd {
	char	*path;
	char	**natme;
	char	**env;
	char	**argv;

	pid_t	*pid;
	int		index_pid;

	int		index;
	int		nbr;
	int		first;
	int		last;

	int		if_here_doc;
	t_fd	fd;
	t_files	files;
}	t_cmd;

int		open_infile(t_lst_cmd *argv, t_cmd *cmd);
void	open_outfile(t_lst_cmd *argv, t_cmd *cmd);

int		main_exec(t_lst_cmd *argv, t_struct_data *s);
void	pipe_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s);
int		setup_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_data *s);
void	exec_cmd(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv);
void	one_cmd_and_builtin(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv);

void	open_and_fill_here_doc(t_cmd *cmd, char *limiter);
void	here_doc(char *limiter, t_cmd *cmd, t_lst_cmd *argv);
void	fill_here_doc(char **read_line, char *limiter, t_cmd *cmd, t_lst_cmd *argv);
int		is_limiter(char *str, char *limiter);
void	get_rand_name(t_cmd *cmd);

int		check_command(t_lst_cmd *argv, t_cmd *cmd);
int		check_access(t_lst_cmd *argv, t_cmd *cmd, char *path);
int		check_slash_and_access(t_lst_cmd *argv, t_cmd *cmd);

void	close_fd_child(t_cmd *cmd);
void	close_fd_parent(t_cmd *cmd);
void	close_fd(t_cmd *cmd);
void	check_close(t_cmd *cmd, int fd);

int		ft_strchr(char *str, char c);
char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, char c);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strcmp_cmd(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_atol(char *str, long *n);
char	*ft_strcat(char *dest, char *src);

void	error_access_cmd(t_lst_cmd *argv, t_cmd *cmd);
void	error_empty_string(t_cmd *cmd);
void	error_cmd(t_lst_cmd *argv, t_cmd *cmd, int exit_code);
void	free_tab(char **tab);
void	free_and_exit(t_cmd *cmd, int exit_code);
void	print_error(t_lst_cmd *argv, t_cmd *cmd);

void	convert_list(t_cmd *cmd, t_lst_cmd *list);
void	convert_list_env(t_cmd *cmd, t_struct_data *s);
int		list_size(t_lst_cmd *list);
int		ft_lst_size_env(t_lst_env *lst_env);

void	init_struct(t_cmd *cmd, t_lst_cmd *argv);
void	init_fd(t_cmd *cmd);
int		set_redirections(t_lst_cmd *argv, t_cmd *cmd);

int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(t_cmd *cmd);

int		builtin_export(t_cmd *cmd, t_struct_data *s);
int		search_replace_export(char *str, t_struct_data *s);
int		search_content_export(char *str, t_struct_data *s);
int		new_line_export(char *str, t_struct_data *s, int nb);
int		new_line_env(char *str, t_struct_data *s);
char	*lets_join_no_egal(char *s1, char *s2);

int		builtin_env(t_cmd *cmd, t_lst_env *env_list);
int		builtin_cd(t_cmd *cmd);
int		builtin_unset(t_cmd *cmd, t_struct_data *s);
int		builtin_exit(t_lst_cmd *argv, t_cmd *cmd);
int		check_builtins(t_cmd *cmd);
int		exec_builtins(t_cmd *cmd, t_struct_data *s, t_lst_cmd *argv);
void	error_builtins(t_cmd *cmd);
int		builtin_arg_nbr(t_cmd *cmd);
int		get_env_line(t_cmd *cmd, char *str);

void	print_export(t_cmd *cmd, t_lst_env *lst_export);
int		its_valid(char *str);
int		check_egal(char *str);
int		its_option(char **argv);

#endif
