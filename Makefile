# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 15:39:24 by fbanzo-s          #+#    #+#              #
#    Updated: 2025/12/04 20:37:15 by fbanzo-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m
BULLET = $(BLUE)•$(RESET)
BULLET_RED = $(RED)•$(RESET)

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

HEADER = includes/philosophers.h

SRCS_FILES = main.c utils.c parser.c data.c philo.c \
mutex.c routine.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR) #-fsanitize=thread
RM = rm -rf

INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ Compilación completada!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)▶ Compilando $(RESET) $<..."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BULLET) $(BLUE)Created:$(RESET) $(OBJ_DIR)/"

clean:
	@echo "$(BULLET_RED) $(RED)Cleaning:$(RESET) object files"
	@$(RM) $(OBJ_DIR) 

fclean: clean
	@echo "$(BULLET_RED) $(RED)Removing:$(RESET) $(NAME)"
	@rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
