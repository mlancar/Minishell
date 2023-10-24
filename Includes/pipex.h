/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/10/24 17:12:09 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cmd_H
# define cmd_H

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
# include "../Sources/Exec/Get_next_line/get_next_line.h"
# include "minishell.h"

typedef struct s_files {
	int		here_doc;
	char	rand_name[7];
	
}	t_files;

typedef	struct s_fd {
	int	read;
	int	write;
	int	close;
	int	previous;
	int	tmp;
	int	pipe[2];
}	t_fd;

typedef struct s_cmd {
	char	*path;
	char	**name;
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

void	open_infile(t_lst_cmd *argv, t_cmd *cmd);
void	open_outfile(t_lst_cmd *argv, t_cmd *cmd);

int		main_exec(t_lst_cmd *argv, t_struct_env *s);
void	pipe_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s);
void	fork_and_exec_cmd(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s);

void	open_and_fill_here_doc(t_cmd *cmd, char *limiter);
void	here_doc(char *limiter, t_cmd *cmd);
void	fill_here_doc(char **read_line, char *limiter, t_cmd *cmd);
int		is_limiter(char *str, char *limiter);

int		check_command(t_lst_cmd *argv, t_cmd *cmd, t_struct_env *s);
int		check_access(t_lst_cmd *argv, t_cmd *cmd, char *path);
int		check_slash_and_access(t_lst_cmd *argv, t_cmd *cmd);

void	close_fd_child(t_lst_cmd *argv, t_cmd *cmd);
void	close_fd_parent(t_lst_cmd *argv, t_cmd *cmd);
void	check_close(int fd);

int		ft_strchr(char *str, char c);
char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, char c);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp_cmd(char *s1, char *s2);

void	error_access_cmd(t_cmd *cmd);
void	error_empty_string(t_cmd *cmd);
void	error_cmd(int return_value, t_cmd *cmd);
void	free_tab(char **tab);
void	free_and_exit(char *str, t_cmd *cmd);

char	**convert_list(t_lst_cmd *list);
char	**convert_list_env(t_struct_env *s);
int		list_size(t_lst_cmd *list);
int		ft_lst_size_env(t_lst_env *lst_env);

void	init_struct(t_cmd *cmd, t_lst_cmd *argv);
void	set_fd(t_cmd *cmd);
void	set_redirections(t_lst_cmd *argv, t_cmd *cmd);

int		builtins_echo(char **argv);
int		builtins_pwd(char **argv);
int		builtins_export(char **argv, t_struct_env *s);
int		builtins_env(char **argv, t_lst_env *env_list);

int		exec_builtins(t_cmd *cmd, t_struct_env *s);
int		its_option(char **argv);
int		its_valid(char *str);
void	print_export(t_lst_env *lst_export);
int		check_egal(char *str);


// void	one_cmd(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list);
// void	first_cmd(t_lst_cmd *argv, t_cmd *cmd);
// void	middle_cmd(t_lst_cmd *argv, t_cmd *cmd);
// void	last_cmd(t_lst_cmd *argv, t_cmd *cmd);
// void	exec_one_cmd(t_lst_cmd *argv, t_cmd *cmd, t_lst_env **env_list);

#endif