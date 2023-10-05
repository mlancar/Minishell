/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/10/05 18:54:54 by malancar         ###   ########.fr       */
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
	int		in;
	int		out;
	int		fd_tmp;
	int		here_doc;
	char	rand_name[7];
	
}	t_files;

typedef struct s_cmd {
	char	*path;
	char	**name;
	int		fd[2];
	int		previous_fd;
	pid_t	*pid;
	int		index_pid;
	int		index;
	int		nbr;
	int		first;
	int		last;
	int		if_here_doc;
	char	**envp;
	char	**argv;
	t_files	files;
	
}	t_cmd;

void	open_infile(t_lst_argv *argv, t_cmd *cmd);
void	open_outfile(t_lst_argv *argv, t_cmd *cmd);

void	pipex(t_lst_argv *argv, t_cmd *cmd);
void	exec_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other);
void	exec_cmds(t_lst_argv *argv, t_cmd *cmd);

void	one_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other);
void	first_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other);
void	middle_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other);
void	last_cmd(t_lst_argv *argv, t_cmd *cmd, int fd_in, int fd_out, int fd_other);


void	open_and_fill_here_doc(t_cmd *cmd, char *limiter);
void	here_doc(char *limiter, t_cmd *cmd);
void	fill_here_doc(char **read_line, char *limiter, t_cmd *cmd);
int		is_limiter(char *str, char *limiter);

int		check_command(t_lst_argv *argv, t_cmd *cmd);
int		check_access(t_lst_argv *argv, t_cmd *cmd, char *path);
void	check_close(int fd);
int		check_slash_and_access(t_lst_argv *argv, t_cmd *cmd);

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

char	**convert_list(t_lst_argv*list);
void	init_struct(t_cmd *cmd, t_lst_argv *argv);
void	init_files(t_lst_argv *argv, t_cmd *cmd);
int		main_pipex(t_lst_argv *argv, char **env);

int		list_size(t_lst_argv*list);

#endif