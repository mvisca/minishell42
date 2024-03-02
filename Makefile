# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 08:55:28 by mvisca            #+#    #+#              #
#    Updated: 2024/02/27 21:20:01 by mvisca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------#
#	FORMAT			#
#-------------------#

RED				:= \033[0;31m
GREEN			:= \033[0;32m
YELLOW			:= \033[0;33m
BLUE			:= \033[0;34m
NC				:= \033[0m

#-------------------#
#	TARGET			#
#-------------------#

NAME			:=	minishell

#-------------------#
#	INGREDIENTS		#
#-------------------#

MS_INC_DIR		:=	include/
MS_INCLUDE		:=	minishell.h

LIB_DIR			:=	lib/libft/
LIB_INC_DIR		:=	$(LIB_DIR)include/
LIB_TGT			:=	$(LIB_DIR)libft.a
LIB_HEAD		:=	$(LIB_INC_DIR)libft.h

RDLN_DIR		:=	lib/readline/
RDLN_INC_DIR	:=	lib/readline/
RDLN_TGT		:=	$(RDLN_DIR)readline.a
RDLN_HEAD		:=	$(RDLN_DIR)readline.h

SRCS_DIR		:=	src/

OBJS_DIR		:=	.build/

FILES			:=	_minishell.c 				\
					debug.c						\
					environment_getters.c		\
					environment_init.c			\
					environment_tools.c			\
					errors_syntax_cases.c		\
					errors_syntax.c				\
					errors.c					\
					initialize.c				\
					interface.c					\
					lexer.c						\
					parser.c					\
					parser_split.c				\
					parser_command_tools.c		\
					parser_redirect_tools.c		\
					utils_free.c				\
					utils_str.c

SRCS			:=	$(FILES:%.c=$(SRCS_DIR)%.c)

OBJS			:=	$(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DEPS			:=	$(OBJS:.o=.d)

DEPS			+=	$(DEPS_LIB)

#-------------------#
#	UTILS			#
#-------------------#

CC				:=	gcc

CFLAGS			:=	-Wall -Wextra -MMD -MP -g -fsanitize=address

DIR_DUP			:=	mkdir -p $(OBJS_DIR)

MAKEFLAGS		+=	--no-print-directory
RM				:=	rm -r -f

#-------------------#
#	RECIPES			#
#-------------------#

all: callforlib $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling $(RED)$@ $(YELLOW)ready! $(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -L./$(RDLN_DIR) -lreadline -lhistory -ltermcap -L./$(LIB_DIR) -lft -I./$(RDLN_INC_DIR) -I./$(LIB_INC_DIR) -I./$(MS_INC_DIR) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c Makefile $(LIB_TGT)
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c $< -I./$(RDLN_INC_DIR) -I./$(LIB_INC_DIR) -I./$(MS_INC_DIR) -o $@
	@echo "$(GREEN)Compiling... $(NC)$(notdir $<) $(RED)-> $(NC)$(notdir $@)"
-include $(DEPS)

$(LIB_TGT): $(LIB_DIR)Makefile $(LIB_HEAD)
	@$(MAKE) -C $(LIB_DIR)

$(RDLN_TGT):
	@$(MAKE) -C $(RDLN_DIR)

callforlib:
	@$(MAKE) -C $(RDLN_DIR)
	@$(MAKE) -C $(LIB_DIR)

clean:
	@echo "$(RED)Deleting objects for... $(NC)$(NAME) *.o *.d $(RED)>> 🗑️$(NC)"
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(LIB_DIR) clean
	@echo "$(RED)Deleting builds for... $(NC)Readline Library $(RED)>> 🗑️$(NC)"
#	@$(MAKE) -C $(RDLN_DIR) clean --silent

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting... $(NC)$(NAME) $(RED)>> 🗑️$(NC)"
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

test1:
	@echo "$(BLUE)$(SRCS)$(NC)"

test2:
	@echo "$(BLUE)$(OBJS)$(NC)"

test3:
	@echo "$(BLUE)$(FILES)$(NC)"

.PHONY: clean fclean re callforlib
