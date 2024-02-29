# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 10:58:55 by fcatala-          #+#    #+#              #
#    Updated: 2023/10/18 15:05:35 by fcatala-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	pipex
CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -MMD -MP

# Main program source file
MAIN_SRC			=	pipex_main.c
BONUS_SRC			=	pipex_main_bonus.c

# Utils 
UTILS_DIR			=	./srcs/
UTILS_PROG			=	parsing.c pipex.c pipex_utils.c
UTILS_SRC			=	$(addprefix $(UTILS_DIR), $(UTILS_PROG))

# Objects and Deps
MAND_OBJ			=	$(MAIN_SRC:.c=.o) $(UTILS_SRC:.c=.o)
MAND_DEPS			=	$(MAIN_SRC:.c=.d) $(UTILS_SRC:.c=.d)
BONUS_OBJ			=	$(BONUS_SRC:.c=.o) $(UTILS_SRC:.c=.o)
BONUS_DEPS			=	$(BONUS_SRC:.c=.d) $(UTILS_SRC:.c=.d)

# Libft
LIBFT_DIR			=	./libft
LIBFT				=	$(LIBFT_DIR)/libft.a

# Targets
all:					$(NAME)

$(NAME):				$(MAND_OBJ) $(LIBFT) 
						$(CC) $(FLAGS) $(MAND_OBJ) $(LIBFT) -o $(NAME)
						@make check_dirs

bonus:					$(BONUS_OBJ) $(LIBFT)
						$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) -o $(NAME)
						@make check_dirs

$(MAND_OBJ):			| lft_update

$(BONUS_OBJ):			| lft_update

$(LIBFT):				
						@make -C $(LIBFT_DIR)

lft_update:				
						@make -C $(LIBFT_DIR)

clean:					
						@rm -f *.o *.d
						@rm -f $(UTILS_DIR)/*.o $(UTILS_DIR)/*.d
						@make clean -C $(LIBFT_DIR)
						@make check_dirs

fclean:										
						@rm -f *.o *.d $(NAME)
						@rm -f $(UTILS_DIR)/*.o $(UTILS_DIR)/*.d
						@make fclean -C $(LIBFT_DIR)
						@make check_dirs

re:						fclean all

check_dirs:
						@echo "\033[32m\nContent of $(LIBFT_DIR):\n\033[0m"
						@ls $(LIBFT_DIR)
						@echo "\033[32m\nContent of pipex directory:\n\033[0m"
						@ls -lF | awk 'NR>1{print $$1 "\t"$$2 "\t"$$6 "-"$$7 "\t"$$8 "\t"$$9}'
						@echo "\033[32m\nContent of ./srcs directory:\n\033[0m"
						@ls -lF ./srcs | awk 'NR>1{print $$1 "\t"$$2 "\t"$$6 "-"$$7 "\t"$$8 "\t"$$9}'
						@echo "\n"

.PHONY: 				all clean fclean re check_dirs bonus lft_update

-include				$(MAND_DEPS) $(BONUS_DEPS)
