# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:59:11 by cbuzzini          #+#    #+#              #
#    Updated: 2025/01/14 16:20:47 by cbuzzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HDR_FILES = pipex.h
SRC_FILES = pipex.c ft_putstr_fd.c ft_putchar_fd.c
OBJ_FILES = $(SRC_FILES:.c=.o)

HDR_BONUS = pipex.h
BONUS_FILES = pipex_bonus.c
OBJ_BONUS = $(BONUS_FILES:.c=.o)

CC = cc 
FLAGS = -g -Wall -Wextra -Werror
NAME = pipex

all: $(NAME)

%.o: %.c $(HDR_FILES) #do I need something parallel to this just for the bonus???
	$(CC) $(FLAGS) -c $< -o $@ -I $(HDR_FILES)

$(NAME): $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME)

#bonus: $(OBJ_BONUS) $(HDR_BONUS)
#	$(CC) $(FLAGS) $(OBJ_BONUS) -I $(HDR_BONUS) -o $(NAME)

clean:
	rm -f $(OBJ_FILES) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus run