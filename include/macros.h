/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:44:43 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/10 18:44:46 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// Debuger switch
# ifndef DEBUG_ON
#  define DEBUG_ON      1
# endif

// Para funciones de validación y otros
# define FALSE          0
# define TRUE           1

// Para acotar casos extremos
# define MAX_PATH_LENGHT	1024
# define MAX_ARGS 			256

// Macros para gestionar fd de entrada y salida
# define FD_IN     0
# define FD_OUT    1
# define FD_HERE   2
# define H_FILE    ".xyz_here_tmp.tmp"

// Macros para pipes
# define R_END   0
# define W_END   1

// Para acotar casos extremos
# define MAX_PATH_LENGHT	1024
# define MAX_ARGS 			256

// Macros para gestionar fd de entrada y salida
# define FD_IN     0
# define FD_OUT    1
# define FD_HERE   2
# define H_FILE    ".xyz_here_tmp.tmp"

// Macros para manipular funciones de LEXER
# define END    	    0
# define DOLLAR			1
# define D_QUOTE		34
# define S_QUOTE		39
# define PIPE			4
# define L_REDIRECT		5
# define R_REDIRECT		6
# define DL_REDIRECT	7
# define DR_REDIRECT	8
# define WORD			9
# define SPACES         " \t\v\n\r"
# define O_CURLY    	123
# define C_CURLY    	125

// Macros para expand
# define NEW            0
# define AUX            1
# define BUF            2

// Para customizar UI con colores ANSI
# define RESET          "\x1b[0m"
# define BLACK          "\x1b[30m"
# define RED            "\x1b[31m"
# define GREEN          "\x1b[32m"
# define YELLOW         "\x1b[33m"
# define BLUE           "\x1b[34m"
# define MAGENTA        "\x1b[35m"
# define CYAN           "\x1b[36m"
# define WHITE          "\x1b[37m"
# define BOLD_BLACK     "\x1b[1;30m"
# define BOLD_RED       "\x1b[1;31m"
# define BOLD_GREEN     "\x1b[1;32m"
# define BOLD_YELLOW    "\x1b[1;33m"
# define BOLD_BLUE      "\x1b[1;34m"
# define BOLD_MAGENTA   "\x1b[1;35m"
# define BOLD_CYAN      "\x1b[1;36m"
# define BOLD_WHITE     "\x1b[1;37m"

// Macro con el título que despliega el prompt
# define TITLE          "💻\001"YELLOW"\002 MiniShell\001"GREEN"\002 "

// Para errores de sintaxis
# define SYNTAX_PIPE_AT_0		1
# define SYNTAX_PIPE_X2			2
# define SYNTAX_BACK_RD_X3		3
# define SYNTAX_FOWARD_RD_X3	4
# define SYNTAX_FAKE_ARROBA_X3	5
# define SYNTAX_CURLY_START     6
# define SYNTAX_CURLY_END   	7

# define SYNTAX_MSSG    "minishell: syntax error near unexpected token `"

// Errores de ejecucion
# define EXIT_DENIED	126
# define EXIT_NOTFOUND	127
# define EXIT_FORK		130
# define EXIT_QUITFORK	131

// No env
# define NOENV "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applicat\
ions/VMware Fusion.app/Contents/Public:/usr/local/go/bin:/usr/local/munki"

#endif
