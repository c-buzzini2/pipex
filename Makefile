# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:59:11 by cbuzzini          #+#    #+#              #
#    Updated: 2025/03/18 17:35:02 by cbuzzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = includes/

HDR_ALL = pipex.h
HDR_BONUS = pipex_bonus.h

HDR_FILES_ALL = $(addprefix $(INCLUDE_DIR), $(HDR_ALL))
HDR_FILES_BONUS = $(addprefix $(INCLUDE_DIR), $(HDR_BONUS))

SRC_FILES = pipex.c \
			ft_putstr_fd.c \
			first_child.c \
			last_child.c \
			pipefd.c \
			execute.c \
			utils.c \
			ft_strcmp.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

BONUS_FILES = pipex_bonus.c \
			ft_putstr_fd.c \
			first_child.c \
			last_child.c \
			pipefd.c \
			execute.c \
			middle_children.c \
			heredoc.c \
			get_next_line.c \
			get_next_line_utils.c \
			utils.c \
			ft_strcmp.c
BONUS = $(addprefix $(SRC_DIR), $(BONUS_FILES))
OBJ_BONUS = $(addprefix $(OBJ_DIR)bonus_, $(BONUS_FILES:.c=.o))

CC = cc 
FLAGS = -g -Wall -Wextra -Werror
NAME = pipex

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR_FILES_ALL)
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)bonus_%.o: $(SRC_DIR)%.c $(HDR_FILES_BONUS)
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -DBONUS -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME)

bonus: $(OBJ_DIR) $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus