# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 17:14:27 by mvisca-g          #+#    #+#              #
#    Updated: 2024/06/08 19:52:25 by mvisca-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------------#
#	FORMAT								#
#---------------------------------------#

RED 		:= \033[0;31m
GREEN 		:= \033[0;32m
YELLOW 		:= \033[0;33m
BLUE 		:= \033[0;34m
NC 			:= \033[0m

#---------------------------------------#
#	TARGET								#
#---------------------------------------#

NAME 		:= libft.a

#---------------------------------------#
#	INGREDIENTS							#
#---------------------------------------#

# Dirs
BUILD_DIR	:= .build/
SRCS_DIR	:= src/
INCS		:= include/

# Sources
SRCS		:=			\
	ft_printf.c			\
	ft_putbasedec.c		\
	ft_putbasehex.c 	\
	ft_putchar.c		\
	ft_putstr.c			\
	ft_atoi.c			\
	ft_atol.c			\
	ft_bzero.c			\
	ft_calloc.c			\
	ft_isalnum.c		\
	ft_isalpha.c		\
	ft_isascii.c		\
	ft_isdigit.c		\
	ft_isprint.c		\
	ft_itoa.c			\
	ft_memchr.c			\
	ft_memcmp.c			\
	ft_memcpy.c			\
	ft_memmove.c		\
	ft_memset.c			\
	ft_putchar_fd.c		\
	ft_putendl_fd.c		\
	ft_putnbr_fd.c		\
	ft_putstr_fd.c		\
	ft_split.c			\
	ft_strchr.c			\
	ft_strdup.c			\
	ft_striteri.c		\
	ft_strjoin.c		\
	ft_strlcat.c		\
	ft_strlcpy.c		\
	ft_strlen.c			\
	ft_strmapi.c		\
	ft_strncmp.c		\
	ft_strnstr.c		\
	ft_strrchr.c		\
	ft_strtrim.c		\
	ft_substr.c			\
	ft_tolower.c		\
	ft_toupper.c		\
	ft_lstadd_back.c	\
	ft_lstadd_front.c	\
	ft_lstclear.c		\
	ft_lstdelone.c		\
	ft_lstiter.c		\
	ft_lstlast.c		\
	ft_lstnew.c			\
	ft_lstsize.c		\
	ft_lstmap.c

SRCS		:= $(SRCS:%=$(SRCS_DIR)%)

# Objects
OBJS		:= $(SRCS:$(SRCS_DIR)%.c=$(BUILD_DIR)%.o)

# Dependencies
DEPS		:= $(OBJS:.o=.d)

#---------------------------------------#
#	UTENSILS							#
#---------------------------------------#

# Compiler
CC 			:= cc

# Compilation flags
CFLAGS 		:= -Wall -Wextra -Werror -fPIC

# PreProcessor flags
CPPFLAGS	:= $(addprefix -I, $(INCS)) -MMD

# Archiver 
AR			:= ar -r -c -s

# Remover
RM			:= rm -f -r

# Make dir
DIR_DUP		= mkdir -p $(@D)

# Default behaviours update
MAKEFLAGS	+= --no-print-directory


#---------------------------------------#
#	RECIPES								#
#---------------------------------------#

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	@$(AR) $@ $(OBJS)
	@echo "$(YELLOW)Packing $(RED)$(NAME) $(YELLOW)ready!$(NC)"

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c Makefile include/libft.h
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo "$(GREEN)Creating... $(NC)$(notdir $<) $(RED)-> $(NC)$(notdir $@)"

clean:
	@echo "$(RED)Deleting objects for... $(NC)libft *.o *.d $(RED)>> 🗑️$(NC)"
	@for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	@$(RM) $(BUILD_DIR)

fclean: clean
	@echo "$(RED)Deleting... $(NC)$(NAME) $(RED)>> 🗑️$(NC)"
	@$(RM) $(NAME)

re: 
	@$(MAKE) fclean 
	@$(MAKE) all

#---------------------------------------#
#	SPEC								#
#---------------------------------------#

.PHONY: clean fclean re all
