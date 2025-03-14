# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:59:11 by cbuzzini          #+#    #+#              #
#    Updated: 2025/03/14 15:25:11 by cbuzzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = includes/

INCLUDES = pipex.h includes/pipex_bonus.h
HDR_FILES = $(addprefix $(INCLUDE_DIR), $(INCLUDES))

SRC_FILES = pipex.c \
			ft_putstr_fd.c \
			first_child.c \
			last_child.c \
			pipefd.c \
			execute.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

BONUS_FILES = pipex_bonus.c \
			ft_putstr_fd.c \
			first_child.c \
			last_child.c \
			pipefd.c \
			execute.c \
			middle_children.c
BONUS = $(addprefix $(SRC_DIR), $(BONUS_FILES))
OBJ_BONUS = $(addprefix $(OBJ_DIR), $(BONUS_FILES:.c=.o))

CC = cc 
FLAGS = -g -Wall -Wextra -Werror
NAME = pipex

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -Iincludes -c $< -o $@ 

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME)

bonus: $(OBJ_DIR) $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus run