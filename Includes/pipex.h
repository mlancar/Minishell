/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:47:18 by malancar          #+#    #+#             */
/*   Updated: 2023/10/04 18:45:35 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_pipex {
	int		infile;
	int		outfile;
	int		here_doc;
	char	*path;
	char	**name;
	int		fd[2];
	int		previous_fd;
	pid_t	*pid;
	int		max;
	int		first;
	int		last;
	int		index_pid;
	int		if_here_doc;
	int		index;
	char	rand_name[7];
	int		fd_tmp;
	char	**envp;
	char	**argv;

}	t_pipex;

//int		init_struct(t_pipex *cmd, int ac);

void	open_infile(t_pipex *cmd, char *first_arg);
void	open_outfile(t_pipex *cmd, char *last_arg);

void	pipex(t_lst_cmd *argv, t_pipex *cmd);
void	first_cmd(t_lst_cmd *argv, t_pipex *cmd);
void	exec_cmd(t_lst_cmd *argv, t_pipex *cmd, int fd_in, int fd_out, int fd_other);

void	open_and_fill_here_doc(t_pipex *cmd, char *limiter);
void	here_doc(char *limiter, t_pipex *cmd);
void	fill_here_doc(char **read_line, char *limiter, t_pipex *cmd);
int		is_limiter(char *str, char *limiter);

int		check_command(t_lst_cmd *argv, t_pipex *cmd);
int		check_access(t_lst_cmd *argv, t_pipex *cmd, char *path);
void	check_close(int fd);
int		check_slash_and_access(t_lst_cmd *argv, t_pipex *cmd);

int		ft_strchr(char *str, char c);
char	**ft_split(char *str, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2, char c);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp_pipex(char *s1, char *s2);

void	error_access_cmd(t_pipex *cmd);
void	error_empty_string(t_pipex *cmd);
void	error_cmd(int return_value, t_pipex *cmd);
void	free_tab(char **tab);
void	free_and_exit(char *str, t_pipex *cmd);

char	**convert(t_lst_cmd *list);
int		init_struct(t_pipex *cmd, t_lst_cmd *argv);
int		main_pipex(t_lst_cmd *argv, char **env);

int		list_size(t_lst_cmd *list);

#endif