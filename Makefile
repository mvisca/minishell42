# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 08:55:28 by mvisca            #+#    #+#              #
#    Updated: 2024/05/08 08:48:54 by mvisca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


RED 		:= \033[0;31m
GREEN 		:= \033[0;32m
YELLOW 		:= \033[0;33m
BLUE 		:= \033[0;34m
NC 			:= \033[0m

NAME        = minishell

HEADER      = ./include/minishell.h

SRC_PATH    = src/
SRC         = 		_minishell.c 				\
					debug.c						\
					environment_getters.c		\
					environment_init.c			\
					environment_tools.c			\
					errors_syntax_cases.c		\
					errors_syntax.c				\
					errors.c					\
					executer_copy.c					\
					expander.c					\
					expander_tools.c			\
					initialize.c				\
					interface.c					\
					lexer.c						\
					parser.c					\
					parser_split.c				\
					parser_split_tools.c		\
					parser_command_tools.c		\
					parser_update_envarr.c		\
					signals.c					\
					utils_free.c				\
					utils_str.c

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

LIBFT_PATH	= lib/libft/
LIBFT		= $(LIBFT_PATH)/libft.a

RLINE_PATH	= lib/readline/
RLINE		= $(RLINE_PATH)/libreadline.a
RLINE_H		= $(RLINE_PATH)/libhistory.a

LIB_PATH	= -L$(LIBFT_PATH) -L$(RLINE_PATH) 
LIB_FLAGS	= $(LIBFT) -lreadline -ltermcap

OBJ_PATH	= .obj/
OBJ			= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEP			= $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))

# para -I (donde *.h)
INC_PATH	= ./includes/ ./lib/ $(LIBFT_PATH) $(RLINE_PATH) 

INC			= $(addprefix -I, $(INC_PATH))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD -g -fsanitize=address
RM			= rm -f

all: $(RLINE) $(OBJ_PATH) subsystems $(NAME)

$(NAME):: $(OBJ) ./$(LIBFT) ./$(RLINE) ./$(RLINE_H)
	@$(CC) $(CFLAGS) $(^) -ltermcap -lreadline -o $(NAME) -g -fsanitize=address
	@echo "$(YELLOW)Packing $(RED)$(NAME) $(YELLOW)ready!$(NC)"
	@echo "$(BLUE)Minishell $(GREEN)compiled! 👍$(NC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(HEADER)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(GREEN)Creating... $(NC)$(notdir $<) $(RED)-> $(NC)$(notdir $@)"

-include $(DEP)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(RLINE):
	@cd lib/readline && ./configure &>/dev/null
	@$(MAKE) -C $(RLINE_PATH) --no-print-directory
	@echo "$(BLUE)Readline $(GREEN)compiled! 👍$(NC)"

subsystems:
	@make -s -C $(LIBFT_PATH)

clean:
#	@$(RM) $(OBJS) $(DEP)
	@$(RM) -rf $(OBJ_PATH)
	@make -s -C $(LIBFT_PATH) clean
	@echo "$(RED)Deleting objects for $(NC) minishell $(RED)>> 🗑️$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@echo "$(RED)Minishell removed >> 🗑️$(NC)"

re: fclean all

cleanrl:
	@make -s -C $(RLINE_PATH) mostlyclean
	@echo "$(RED)Readline removed >> 🗑️$(NC)"

# Phony
.PHONY: all clean fclean re cleanrl
