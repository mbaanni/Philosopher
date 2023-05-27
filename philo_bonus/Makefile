# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 09:57:14 by mbaanni           #+#    #+#              #
#    Updated: 2023/05/25 15:29:51 by mbaanni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG= -Wall -Wextra -Werror
CC= cc
SRC= main.c atoi.c routine.c creat_list.c clean_up.c monitor.c creat_philo.c
OBG= $(SRC:.c=.o)
NAME= philo_bonus
all : $(NAME)

$(NAME) : $(OBG)
	$(CC)  $(FLAG) $(OBG) -o $(NAME)
clean :
	rm -rf *.o
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONY: all clean fclean re