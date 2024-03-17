#ifndef MACROS_H
# define MACROS_H

// Para funciones de validación y otros
# define FALSE  0
# define TRUE   1

// Macros para gestionar fd de entrada y salida
// XAVI:: Está ok que in sea 0 y out sea 1 ?? O es al revés ??
# define FD_IN     0
# define FD_OUT    1
# define FD_HERE   2
# define H_FILE    ".xyz_here_tmp.tmp"

// Macros con el título que despliega el prompt
# define TITLE "💻 \x1b[33mMiniShell \x1b[1;35m@ \x1b[0m"
// falta definir titulo heredoc similar a heredoc>

// Macros para pipes
# define R_END   0
# define W_END   1

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

// Para customizar UI con colores ANSI
# define RESET       "\x1b[0m"
# define BLACK       "\x1b[30m"
# define RED         "\x1b[31m"
# define GREEN       "\x1b[32m"
# define YELLOW      "\x1b[33m"
# define BLUE        "\x1b[34m"
# define MAGENTA     "\x1b[35m"
# define CYAN        "\x1b[36m"
# define WHITE       "\x1b[37m"
# define BOLD_BLACK  "\x1b[1;30m"
# define BOLD_RED    "\x1b[1;31m"
# define BOLD_GREEN  "\x1b[1;32m"
# define BOLD_YELLOW "\x1b[1;33m"
# define BOLD_BLUE   "\x1b[1;34m"
# define BOLD_MAGENTA "\x1b[1;35m"
# define BOLD_CYAN   "\x1b[1;36m"
# define BOLD_WHITE  "\x1b[1;37m"

// Para errores de sintaxis
# define SYNTAX_PIPE_AT_0		1
# define SYNTAX_PIPE_X2			2
# define SYNTAX_BACK_RD_X3		3
# define SYNTAX_FOWARD_RD_X3	4
# define SYNTAX_FAKE_ARROBA_X3	5
# define SYNTAX_CURLY_START     6
# define SYNTAX_CURLY_END   	7

# define SYNTAX_MSSG "minishell: syntax error near unexpected token `"

#endif
