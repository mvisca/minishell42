/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:44:43 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/09 11:50:31 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// Para funciones de validación y otros
# define FALSE          0
# define TRUE           1

// Para manejar el modo de las señales 
# define INTERACTIVE    1
# define HEREDOC        2

// Macros para gestionar fd de entrada y salida
# define FD_IN     0
# define FD_OUT    1
# define FD_HERE   2
# define H_FILE    "xyz_here_tmp.tmp"

// Macros para pipes
# define R_END   0
# define W_END   1

// Para acotar casos extremos.Solo utiliza MAX_PATH
# define MAX_PATH	1024
# define MAX_ARGS	256

/*
// Macros para gestionar fd de entrada y salida: esta repe?
# define FD_IN     0
# define FD_OUT    1
# define FD_HERE   2
# define H_FILE    "xyz_here_tmp.tmp"
*/

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
# define O_PARENTH    	40
# define C_PARENTH    	41
# define O_SQUARE    	91
# define C_SQUARE   	93

// Macros para expand
//# define NEW            0
//# define AUX            1
//# define BUF            2

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

// Mensajes de error
// warning: here-document at line 1 delimited by end-of-file (wanted `EOF')
# define SYNTAX_MSSG    "Minishell: syntax error near unexpected token `"
# define MINI			"Minishell: "
# define DUP_FAIL		"dup2 failed "
# define NO_PIPE		": unable to create a pipe\n"
# define NO_FORK		": Resource temporarily unavailable\n"
# define NO_FOUND 		": command not found\n"
# define IS_DIR			": is a directory\n"
# define IS_NO_DIR		": Not a directory\n"
# define NO_FILE		": No such file or directory\n"
# define NO_EXEC		": Permission denied\n"
# define NO_OLD			": OLDPWD not set\n"
# define NO_HOME		": HOME not set\n"
# define NO_CWD			"cd: error retrieving current directory: "
# define NO_GETCWD		"getcwd: cannot access parent directories"

// Errores de ejecucion
# define EXIT_DENIED	126
# define EXIT_NOTFOUND	127
# define EXIT_FORK		130
# define EXIT_QUITFORK	131

// Signals mode
# define INTERACTIVE 	1
# define HEREDOC 		2

// No env
# define AUTOENV "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

#endif
