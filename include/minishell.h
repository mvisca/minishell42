#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>

# include "macros.h"
# include "structures.h"
# include "../lib/libft/include/libft.h"

/*##################	BUILTINS	#####################*/

/*##################	DEBUG		#####################*/

void    	debug_print_token(t_tokl *token, int i);
void        debug_token(t_ms *ms);
void        debug_command(t_ms *ms);

/*##################	ENVIRONMENT	#####################*/

t_envl	    *environment_init(t_ms *ms, char **envp);

t_envl  	*environment_new_node(t_ms *ms, char *key, char *value);
t_envl  	*environment_add_node(t_ms *ms, t_envl *envnode);
void		environment_del_node(t_ms *ms, char *key);

t_envl  	*environment_get_node(t_ms *ms, char *key);
char		*environment_get_value(t_ms *ms, char *key);

/*##################	ERRORS		#####################*/

// System errors
void		error_exit(char *msj, t_ms *ms);
void		error_free_exit(char *msj, t_ms *ms);

// User errors
int			errors_syntax(t_ms *ms);
int			errors_syntax_curly_brackets(char *line);

/*##################	EXECUTOR	#####################*/

/*##################	EXPANSOR	#####################*/

/*##################	INITIALIZER	#####################*/

void		initialize(t_ms *ms, int ac, char **av, char **envp);

/*##################	INTERFACE	#####################*/

int	    	interface_get_line(t_ms *ms);

/*##################	LEXER		#####################*/

int			lexer(t_ms *ms, char *line);

int			lexer_make_token(t_ms *ms, char *line, int type);
char		*lexer_make_token_word(char *line);
t_tokl	    *lexer_add_token(t_ms *ms, t_tokl *token);
int 	    lexer_end_token(t_ms *ms);

void    	lexer_skip_empty_token(t_ms *ms); 

/*##################	PARSER		#####################*/

int			parser(t_ms *ms);

t_coml		*parser_alloc_command(void);
int			parser_add_command(t_ms *ms, t_coml *command);

int         parser_pre(t_coml **cmnd, t_tokl *start);

int			parser_alloc_add_redir(t_coml *command);
int			parser_init_redir(t_coml *command, t_tokl *token);

// int         parser_count_words(char *str);
// int         parser_count_commands(t_tokl *token);

/*##################	UTILS		#####################*/

int 		utils_free_ms(t_ms *ms);
void		utils_free_tab(char **tab);
void		utils_free_env_list(t_envl *env);
void		utils_free_token_list(t_tokl *token);
void		utils_free_comnd_list(t_coml *comnd);

char        *str_clean_spaces(char *str);
int         str_only_spaces(char *str);

t_tokl      *str_ext_cmnd(t_coml **cmnd, char *str);

// int			array_append(t_coml *comnd, t_tokl *start);

#endif
