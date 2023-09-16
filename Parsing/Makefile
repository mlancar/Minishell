# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auferran <auferran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 17:16:20 by auferran          #+#    #+#              #
#    Updated: 2023/09/16 17:16:21 by auferran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADER = minishell.h

SRCS =	main.c minishell.c manage_sig.c utils.c\
		init_struct.c check_prompt.c error.c free_all.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC = cc

FLAGS = -Wall -Werror -Wextra -g

$(NAME) : $(OBJS) $(HEADER)
		 $(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -MMD -c $< -o $@
all : $(NAME)

clean :
		rm -f $(OBJS) $(DEPS)

fclean : clean
		rm -f $(NAME) $(DEPS)

re : fclean all

-include : $(DEPS)

.PHONY: all clean fclean re
