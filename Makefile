# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 19:06:48 by malancar          #+#    #+#              #
#    Updated: 2023/10/25 16:45:11 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

FLAGS	:= -Wextra -Werror -Wall -g 

NAME	= minishell

HEADER = ./Includes
HDR = $(HEADER)/pipex.h $(HEADER)/minishell.h

SOURCES_PARSING =	main.c                  \
                    manage.c                \
                    manage_sig.c            \
                    utils.c				    \
                    fill_lst.c			    \
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
                    init_lst_env_2.c			\
                    lst_env_utils.c	        \
                    manage_dollar.c		    \
                    manage_dollar_utils.c	\
                    token.c				    \
                    quote_2.c               \
					
					
SOURCES_EXEC =		check.c							\
                    init.c							\
                    convert.c						\
                    new_exec_cmds.c					\
                    pipex_utils.c					\
                    pipex_utils_2.c					\
                    ft_split.c						\
                    open_files.c					\
                    error_and_free.c				\
                    main_pipex.c					\
                    here_doc.c						\
                    close.c							\
					builtins_echo.c					\
					builtins_env.c					\
					builtins_export.c				\
					builtins_pwd.c					\
					builtins_export_2.c				\
					builtins.c				        \
                    Get_next_line/get_next_line.c	\
                    Get_next_line/get_next_line_utils.c

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