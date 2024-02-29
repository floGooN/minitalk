# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 20:22:12 by fberthou          #+#    #+#              #
#    Updated: 2024/02/29 13:41:31 by fberthou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- SET VARIABLES --- #
RESET_COLOR	= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

CNAME		= client
SNAME		= server
LIBFT		= $(LIB_DIR)/libft.a

SRC_DIR	= ./sources
SRC_DIR	= ./sources
LIB_DIR		= ./libft
BUILD_DIR	= .build

MINIT_HDR_DIR	= ./headers
LIBFT_HDR_DIR	= $(LIB_DIR)/hdr

CFLAGS		= -Wall -Wextra -Werror -g3 -I$(LIBFT_HDR_DIR) -I$(MINIT_HDR_DIR)
DEPFLAGS	= $(CFLAGS) -MM -MT $(BUILD_DIR)/$*.o -MF $@ $<

# --- SOURCES FILES --- #
CSRC		= client.c utils.c c_utils.c
SSRC		= server.c utils.c s_utils.c sigman.c

# ---- TEMP FILES ---- #
C_OBJ	= $(CSRC:%.c=$(BUILD_DIR)/%.o)
C_DEP	= $(CSRC:%.c=$(BUILD_DIR)/%.d)
S_OBJ	= $(SSRC:%.c=$(BUILD_DIR)/%.o)
S_DEP	= $(SSRC:%.c=$(BUILD_DIR)/%.d)

# --- CALL --- #
default	: all
all		: $(LIBFT) $(SNAME) $(CNAME)

# --- CLIENT --- #
$(CNAME)	: $(C_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)-- client ready --$(RESET_COLOR)"

# --- SERVER --- #
$(SNAME)	: $(S_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)-- server ready --$(RESET_COLOR)"

# --- LIBRAIRIE --- #
$(LIBFT)	: FORCE
	@$(MAKE) -C libft/ all

# --- OBJECTS --- #
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# --- DEPENDENCES --- #
$(BUILD_DIR)/%.d : $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(DEPFLAGS)

FORCE	:

# --- CLEAN MANAGEMENT --- #
clean	:
	@rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_DIR)/ clean
	@echo "$(YELLOW)-- removed temporary files --$(RESET_COLOR)"

fclean	: 
	$(MAKE) -C $(LIB_DIR)/ fclean
	@rm -rf $(BUILD_DIR) $(CNAME) $(SNAME)
	@echo "$(YELLOW)-- removed server / client --$(RESET_COLOR)"

re		: fclean all

-include $(C_DEP) $(S_DEP)

.PHONY	: clean fclean re FORCE default all