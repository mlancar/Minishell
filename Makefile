# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 19:06:48 by malancar          #+#    #+#              #
#    Updated: 2023/10/04 18:36:19 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

FLAGS	:= -Wextra -Werror -Wall -g 

NAME	= minishell

HEADER = ./Includes
HDR = $(HEADER)/pipex.h $(HEADER)/minishell.h

SOURCES_PARSING =	main.c				\
					manage.c			\
					manage_sig.c		\
					utils.c				\
					fill_lst.c			\
					dup_str.c			\
					check_prompt.c		\
					error.c				\
					lst_utils_cmd.c		\
					lst_utils_arg.c		\
					lst_utils_file.c	\
					quote.c				\
					prompt_utils.c		\
					free_all.c
					
SOURCES_EXEC =		check.c								\
					convert.c							\
		  			old_pipex.c								\
		  			pipex_utils.c						\
		  			pipex_utils_2.c						\
		  			ft_split.c							\
		  			open_files.c						\
		  			error_and_free.c					\
		  			main_pipex.c						\
		  			here_doc.c							\
				  	Get_next_line/get_next_line.c		\
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
			$(CC) $(FLAGS) -lreadline -o $(NAME) $(OBJS)

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
