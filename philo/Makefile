# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 09:57:14 by mbaanni           #+#    #+#              #
#    Updated: 2023/05/27 19:03:59 by mbaanni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG= -Wall -Wextra -Werror
CC= cc
SRC= main.c atoi.c routine.c creat_list.c clean_up.c monitoring.c creat_mutex.c
OBG= $(SRC:.c=.o)
NAME= philo
all : $(NAME)

$(NAME) : $(OBG)
	$(CC)  $(FLAG) $(OBG) -o $(NAME) 
clean :
	rm  -rf $(OBG)
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONY: all clean fclean re
