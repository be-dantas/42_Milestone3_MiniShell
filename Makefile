# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 10:45:53 by bedantas          #+#    #+#              #
#    Updated: 2025/10/24 18:17:19 by bedantas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC_DIR     = src
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(LIBFT_DIR) -I$(SRC_DIR) -Iutils

SRCS        = $(wildcard $(SRC_DIR)/*.c)
OBJS        = $(SRCS:.c=.o)

# ************************* COLORS & SILENCE ************************* #

RESET       = \033[0m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
RED         = \033[1;31m

SILENT 		= @

# ****************************** RULES ******************************* #

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(SILENT)echo "$(GREEN)[MINISHELL]$(RESET) Compilado"
	$(SILENT)$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lreadline

$(LIBFT_LIB):
	$(SILENT)echo "$(YELLOW)[LIBFT]$(RESET) Compilado"
	$(SILENT)$(MAKE) -C $(LIBFT_DIR) -s

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ***************************** CLEANING ***************************** #

clean:
	$(SILENT)echo "$(RED)[CLEAN]$(RESET) Removidos: objetos do projeto"
	$(SILENT)rm -f $(OBJS)
	$(SILENT)$(MAKE) clean -C $(LIBFT_DIR) -s

fclean: clean
	$(SILENT)echo "$(RED)[FCLEAN]$(RESET) Removidos: binário e libft.a"
	$(SILENT)rm -f $(NAME)
	$(SILENT)$(MAKE) fclean -C $(LIBFT_DIR) -s

re: fclean all

.PHONY: all clean fclean re
