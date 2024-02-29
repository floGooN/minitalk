# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 17:36:11 by fberthou          #+#    #+#              #
#    Updated: 2024/02/22 21:53:21 by fberthou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET_COLOR	= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

NAME		= libft.a

SRC_DIR		= ./src
SRC_LST		= $(SRC_DIR)/src.mk
HDR_DIR		= ./hdr
BUILD_DIR	= .build

CFLAGS		= -Wall -Wextra -Werror -g -I$(HDR_DIR)
DEPFLAGS	= $(CFLAGS) -MM -MT $(BUILD_DIR)/$*.o -MF $@ $<

-include $(SRC_LST)
OBJ		= $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP		= $(SRC:%.c=$(BUILD_DIR)/%.d)

# --- CALL --- #
default : all
all : $(NAME)

# --- ARCHIVE --- #
$(NAME) : $(OBJ)
	@ar -rcs $@ $^
	@echo "$(GREEN)-- generated archive --$(RESET_COLOR)"

# --- OBJECTS --- #
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# --- DEPENDENCES --- #
$(BUILD_DIR)/%.d : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(DEPFLAGS)

# --- CLEAN MANAGEMENT --- #
clean :
	@rm -rf $(BUILD_DIR)

fclean : clean
	@rm -f $(NAME)
	@echo "$(YELLOW)-- removed archived --$(RESET_COLOR)"

re : fclean all

.PHONY :
	all clean fclean re

