# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 19:06:48 by malancar          #+#    #+#              #
#    Updated: 2023/11/23 23:06:53 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

FLAGS	:= -Wextra -Werror -Wall -g

NAME	= minishell

HEADER = ./Includes
HDR = $(HEADER)/exec.h $(HEADER)/minishell.h

SOURCES_PARSING =	main.c                  \
                    manage.c                \
                    manage_sig.c            \
                    utils.c				    \
					utils_2.c				\
                    fill_lst.c			    \
                    fill_lst_arg.c          \
                    fill_lst_file.c         \
                    dup_str.c               \
                    check_prompt.c          \
                    error.c		            \
                    lst_cmd_utils.c		    \
                    lst_arg_utils.c		    \
                    lst_file_utils.c        \
                    quote.c			        \
                    prompt_utils.c	        \
                    free_all.c	            \
                    init_lst_env.c	        \
                    init_lst_env_2.c		\
					init_lst_env_3.c		\
					init_lst_env_4.c		\
                    lst_env_utils.c	        \
					update_shlvl.c			\
                    manage_dollar.c		    \
                    manage_dollar_2.c       \
                    manage_dollar_utils.c	\
                    manage_dollar_query.c   \
                    token.c				    \
                    quote_2.c               \
                    itoa.c                  \



SOURCES_EXEC =		Builtins/builtin_echo.c				\
					Builtins/builtin_env.c				\
					Builtins/builtin_export.c			\
					Builtins/builtin_pwd.c				\
					Builtins/builtin_export_2.c			\
                    Builtins/builtin_export_3.c     	\
                    Builtins/builtin_unset.c        	\
                    Builtins/builtin_cd.c				\
					Builtins/builtin_cd_2.c				\
                    Builtins/builtin_exit.c				\
					Builtins/builtins.c					\
					Builtins/builtins_utils.c			\
					check.c								\
                    check_access.c						\
                    close.c								\
                    wait_cmds.c					       	\
                    convert.c							\
                    here_doc.c							\
                    init.c								\
                    exec_cmd.c                          \
					exec_setup.c						\
                    utils_exec.c						\
                    utils_exec_2.c						\
                    error_and_print.c   				\
                    error_and_close.c                   \
					free.c								\
                    ft_split.c							\
                    Get_next_line/get_next_line.c		\
                    Get_next_line/get_next_line_utils.c	\
                    open_files.c						\
					print_fd.c							\
                    redirections.c						\
					signal.c

SRCS_PARSING = $(addprefix ./Sources/Parsing/, $(SOURCES_PARSING))

SRCS_EXEC = $(addprefix ./Sources/Exec/, $(SOURCES_EXEC))

OBJECTS =	$(SRCS_PARSING:.c=.o) $(SRCS_EXEC:.c=.o)
OBJS = $(addprefix Objects/, $(OBJECTS))

DEPENDENCIES = $(SOURCES_PARSING:.c=.d) $(SOURCES_EXEC:.c=.d)
DEPS = $(addprefix ./Objects/, $(DEPENDENCIES))

RM = rm -rf


all:	 $(NAME)

$(NAME):	Objects/ $(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lreadline

Objects/%.o: 	%.c
				@mkdir -p $(dir $@)
				@$(CC) $(FLAGS) -MMD -I $(HEADER) -I Sources/Get_next_line -o $@ -c $<

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME) $(DEPS)

re:	fclean all

Objects/:
			mkdir -p Objects

Objects:
		mkdir -p Objects

.PHONY: all clean fclean re
