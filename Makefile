# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 08:55:28 by mvisca            #+#    #+#              #
#    Updated: 2024/04/16 19:51:51 by mvisca-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEF_COLOR	:=	\033[1;97m
PINK		:=	\033[1;95m
GREEN		:=	\033[1;92m
CIAN		:=	\033[1;96m

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
					executer.c					\
					expander.c					\
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

OBJ_PATH	= ./.obj/
OBJ			= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEP			= $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))

# para -I (donde *.h)
INC_PATH	= ./includes/ ./lib/ $(LIBFT_PATH) $(RLINE_PATH) 

INC			= $(addprefix -I, $(INC_PATH))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD 
RM			= rm -f

all: $(RLINE) $(OBJ_PATH) subsystems $(NAME)

clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(RM) -rf $(OBJ_PATH)
	@make -s -C $(LIBFT_PATH) clean
	@echo "$(PINK)Objects removed$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@echo "$(PINK)Minishell removed$(DEF_COLOR)"

re: fclean all

cleanrl:
	@make -s -C $(RLINE_PATH) mostlyclean
	@echo "$(PINK)READLINE removed$(DEF_COLOR)"

$(NAME)::  $(OBJ) ./$(LIBFT) ./$(RLINE) ./$(RLINE_H)
	@$(CC) $(CFLAGS) $(^) -ltermcap -lreadline -o $(NAME) -g -fsanitize=address
	@echo "$(GREEN)MINISHELL compiled :D$(DEF_COLOR)"

subsystems:
	@make -s -C $(LIBFT_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(RLINE):
	@cd lib/readline && ./configure &>/dev/null
	@$(MAKE) -C $(RLINE_PATH) --no-print-directory
	@echo "$(CIAN)READLINE compiled$(DEF_COLOR)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include ${DEP}

# Phony
.PHONY: all clean fclean re cleanrl