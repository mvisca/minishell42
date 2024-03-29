# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 08:55:28 by mvisca            #+#    #+#              #
#    Updated: 2024/03/12 10:12:17 by mvisca           ###   ########.fr        #
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

# Headers
INC				:=	./include
MS_H			:=	$(INC)/minishell.h
OTHER_H			:=	$(INC)/macros.h $(INC)/structures.h

# Libft
LFT				:=	./lib/libft
LFT_INC			:=	$(LFT)/include
LFT_INC_H		:=	$(LIB_LFT_INC)/libft.h
LFT_A			:=	$(LIB_LFT)/libft.a

# Readline
RL				:=	./lib/readline
RL_RL_A			:=	$(RL)/libreadline.a
RL_HY_A			:=	$(RL)/libhistory.a

# Complier flags, incs
INCS_PATH		:=	-I $(LFT_INC) -I $(RL)

# Compiler flags, libs
LIBS_PATH		:=	-L $(LFT) -L $(RL)
LIBS_PACK		:=	-lft -lreadline -ltermcap

# Source directory
SRC				:=	src/

# Source files
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
					parser_update_envarr.c		\
					signals.c					\
					utils_free.c				\
					utils_str.c

# Sources absolute path
SRCS			:= $(addprefix $(SRC), $(FILES))

# Object directory
BUILD			:=	.obj/

# Objects absolute path
OBJS			:=	$(addprefix $(BUILD), $(FILES:.c=.o))

# Dependencies absolute path
DEPS			:=	$(addprefix $(BUILD), $(OBJS:.o=.d))

#-------------------#
#	UTILS			#
#-------------------#

CC				:=	gcc

CFLAGS			:=	-Wall -Wextra -MMD -MP -g -fsanitize=address

DIR_DUP			:=	mkdir -p $(BUILD)

MAKE_FLAGS		+=	--no-print-directory

RM				:=	rm -r -f

#-------------------#
#	RECIPES			#
#-------------------#

all: callforlib $(NAME)

$(NAME): $(OBJS) $(LFT_A) $(RL_RL_A) $(RL_HY_A)
	@echo "$(YELLOW)Compile... $(RED)$@ $(YELLOW)ready! $(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS_PATH) $(LIBS_PACK) -o $(NAME)

$(BUILD)%.o: $(SRC)%.c Makefile $(LFT_A) $(RL_RL_A) $(RL_HY_A) $(BUILD)
	@$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@
	@echo "$(GREEN)Compile... $(NC)$(notdir $<) $(RED)-> $(NC)$(notdir $@)"
-include $(DEPS)

$(BUILD):
	@$(DIR_DUP)
	@echo "$(GREEN)Create $(NC)$(@) ready! $(NC)"

$(LFT_A): $(LFT)/Makefile
	@$(MAKE) -C $(LFT) $(MAKE_FLAGS)

$(RL_RL_A):
	@$(MAKE) -C $(RL) $(MAKE_FLAGS)

callforlib:
#	@cd $(RL) && ./configure &>/dev/null
#	@$(MAKE) -C $(RL) $(MAKE_FLAGS)
#	@echo "$(YELLOW)Build... $(RED)readline $(YELLOW)ready! $(NC)"
	@$(MAKE) -C $(LFT) $(MAKE_FLAGS)

clean:
	@echo "$(RED)Deleting objects for... $(NC)$(NAME) *.o *.d $(RED)>> 🗑️$(NC)"
	@$(RM) $(BUILD)
	@$(MAKE) -C $(LFT) clean $(MAKE_FLAGS)
#	@echo "$(RED)Deleting all for... $(NC)readline $(RED)>> 🗑️$(NC)"
#	@$(MAKE) -C $(RL) clean $(MAKE_FLAGS)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting... $(NC)$(NAME) $(RED)>> 🗑️$(NC)"
	@$(MAKE) -C $(LFT) fclean $(MAKE_FLAGS)

re: fclean all

.PHONY: clean fclean re callforlib
