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
# include <stddef.h>
# include <stdint.h>
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

typedef struct s_fd {
	int	read;
	int	write;
	int	other_pipe;
	int	previous;
	int	tmp;
	int	pipe[2];
}	t_fd;

typedef struct s_cmd {
	char	*path;
	char	**name;
	char	**env;
	int		*fd_hd;
	pid_t	*pid;
	int		index;
	int		nbr;
	int		first;
	int		last;

	int		heredoc;
	t_fd	fd;
	t_files	files;
}	t_cmd;

int		open_infile(t_cmd *cmd, char *infile);
int		open_outfile(t_lst_cmd *cmd_list, t_cmd *cmd, char *outfile);
int		open_heredoc(t_cmd *cmd, int *fd, t_struct_data *s, char *limiter);

int		redirection_one_cmd(t_lst_cmd *cmd_list, t_cmd *cmd);
int		heredoc_redirections(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s);
int		fork_heredoc(char *limiter, t_cmd *cmd, t_lst_cmd *cmd_list,
			t_struct_data *s);
int		is_limiter(char *str, char *limiter);
void	get_rand_name(t_struct_data *s, t_cmd *cmd);

int		start_exec(t_lst_cmd *cmd_list, t_struct_data *s);
int		exec(t_struct_data *s, t_cmd *cmd);
void	pipe_cmd(t_struct_data *s, t_cmd *cmd);
void	exec_child(t_cmd *cmd, t_struct_data *s);
void	exec_cmd(t_cmd *cmd, t_struct_data *s);
void	loop_exec(t_lst_cmd *cmd_list, t_cmd *cmd, t_struct_data *s);
void	one_cmd_builtin(t_cmd *cmd, t_struct_data *s);

void	close_all_fd(t_cmd *cmd);
void	close_fd_hd(t_cmd *cmd);
void	close_fd_child(t_cmd *cmd);
void	close_fd_parent(t_cmd *cmd);
void	check_close(int *fd);

void	wait_cmd(t_cmd *cmd);

int		is_command_valid(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd);
int		check_access(t_struct_data *s, t_lst_cmd *cmd_list, t_cmd *cmd,
			char *path);
int		check_slash_and_access(t_lst_cmd *cmd_list, t_cmd *cmd);

int		ft_strchr(char *str, char c);
int		ft_atol(char *str, long *n);
int		ft_strcmp_cmd(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char *s1, char *s2, char c);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_calloc(size_t nmemb, size_t size);

void	ignore_signal(void);
void	restore_signal(void);
void	signal_heredoc(int signal);
void	ft_singleton(int mode, t_cmd *cmd, t_lst_cmd *cmd_list,
			t_struct_data *s);

void	free_and_set(t_cmd *cmd, char **array);
void	free_exec(t_cmd *cmd);
void	free_tab(char **tab);
void	free_and_exit(t_struct_data *s, t_cmd *cmd, int exit_code);
void	free_and_close_hd(t_struct_data *s, t_cmd *cmd);

void	error_access_slash(t_cmd *cmd);
void	error_open_file(t_cmd *cmd, char *infile, char *outfile);
void	error_dir(t_cmd *cmd, int exit_code);
void	error_exec(t_struct_data *s, t_cmd *cmd, int exit_code);
void	error_access_cmd(t_struct_data *s, t_cmd *cmd);
void	error_cmd(t_struct_data *s, t_cmd *cmd, int exit_code);
void	print_error(t_cmd *cmd);

int		list_size(t_lst_cmd *list);
int		ft_lst_size_env(t_lst_env *lst_env);
void	convert_list(t_cmd *cmd, t_lst_cmd *list);
void	convert_list_env(t_cmd *cmd, t_struct_data *s);

void	init_struct(t_cmd *cmd, t_lst_cmd *name);
void	init_fd(t_cmd *cmd);

void	builtin_export(t_cmd *cmd, t_struct_data *s);
void	builtin_echo(t_cmd *cmd);
void	builtin_pwd(t_cmd *cmd);
void	builtin_env(t_cmd *cmd, t_lst_env *env_list);
void	builtin_cd(t_cmd *cmd, t_struct_data *s);
void	builtin_unset(t_cmd *cmd, t_struct_data *s);
void	builtin_exit(t_cmd *cmd, t_struct_data *s);

int		its_pwd(char *str);
int		its_oldpwd(char *str);
int		search_replace_export(char *str, t_struct_data *s);
int		search_content_export(char *str, t_struct_data *s);
int		new_line_export(char *str, t_struct_data *s, int nb);
int		new_line_env(char *str, t_struct_data *s);
int		check_builtins(t_cmd *cmd);
int		exec_builtins(t_cmd *cmd, t_struct_data *s);
int		builtin_arg_nbr(t_cmd *cmd);
int		get_env_line(t_cmd *cmd, char *str);
int		its_valid(char *str, t_cmd *cmd);
int		check_egal(char *str);
int		its_option(char **name);
char	*lets_join_no_egal(char *s1, char *s2);
void	error_builtins(t_cmd *cmd, char *str, int exit_code);
void	print_export(t_cmd *cmd, t_lst_env *lst_export);

#endif
