# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 18:23:44 by malancar          #+#    #+#              #
#    Updated: 2023/09/16 19:03:08 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

RM	= rm -f

NAME	= minishell

CFLAGS	= -Wextra -Werror -Wall -g -O3



all:	 $(NAME)

$(NAME):	
		make -C ./Exec all
		make -C ./Parsing all

clean:
		make -C ./Exec clean
		make -C ./Parsing all
		
fclean: clean
	

re:	fclean all

.PHONY: all clean fclean re mlx