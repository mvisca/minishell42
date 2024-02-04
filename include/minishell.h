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

/*##################	ENVIRONMENT	#####################*/

/*##################	ERRORS		#####################*/

/*##################	EXECUTOR	#####################*/

/*##################	EXPANSOR	#####################*/

/*##################	INITIALIZER	#####################*/

/*##################	LEXER		#####################*/

/*##################	PARSER		#####################*/

/*##################	UTILS		#####################*/


// ms_builtin_cd.c
// void		ms_cd(t_minishell *ms, t_tokenlst *token);

// ms_builtins_env.c
void		ms_env(t_minishell *ms);

// ms_builtins_export.c
// void		ms_export(t_minishell *ms, t_tokenlst *tolen);

// ms_builtins_echo.c
// void		ms_echo(t_minishell *ms, char *args[]);

// void		ms_unset(t_minishell *ms, char *args[]);
// ms_builtins_unset.c

// ms_builtins_exit.c
// void		ms_exit(t_minishell *ms);

/*#####################
EXECUTOR
#####################*/

void		ms_executor(t_minishell *ms);
// ms_command_processor.c
// void		ms_command_processor(t_minishell *ms);

// // ms_syscal_*.c
// void		ms_syscall_fstchld(t_minishell *ms, t_tokenlst *token);
// void		ms_syscall_mddlchld(t_minishell *ms, t_tokenlst *token);
// void		ms_syscall_lstchld(t_minishell *ms, t_tokenlst *token);

/*#####################
ENVIROMENT
#####################*/

// ms_env_init.c
t_envlst	*ms_env_init(t_minishell *ms);

// ms_env_getters.c
t_envlst	*ms_getenv_node(t_minishell *ms, char *str);
char		*ms_getenv_value(t_minishell *ms, char *str);

// ms_env_tools.c
t_envlst	*ms_addenv_node(t_minishell *ms, t_envlst *envnode);
t_envlst	*ms_newenv_node(t_minishell *ms, char *env_var, char *env_value);
void		ms_deleteenv(t_minishell *ms, char *env_var);
void		ms_updateenv(t_minishell *ms, char *env_var, char *env_value);

/*#####################
ERRORS
#####################*/

// ms_errors.c
// void		ms_put_error(t_minishell *ms, t_tokenlst *token, char *str);
void		ms_error_exit(char *msj, t_minishell *ms);
void		ms_error_free_exit(char *msj, t_minishell *ms);

/*#####################
FREE
#####################*/

// ms_free.c
void		ms_free_str(char *str);
void		ms_free_tab(char **tab);
// void		ms_free_tokenlst(t_tokenlst *token);
void		ms_free_envlst(t_envlst *env);
void		ms_free_ms(t_minishell *ms);

/*#####################
INPUT
#####################*/

// ms_get_line.c
void		ms_get_line(t_minishell *ms);

/*#####################
STRUCTURE INIT
#####################*/

// ms_init.c
void		ms_init(t_minishell *ms, int ac, char **av, char **envp);

/*#####################
LEX & PARSE
#####################*/

// ms_lexer.c
//void		ms_lexer(t_minishell *ms);
char		**tokenize_string(const char *input, int *token_count);


// ms_lexertmp.c
void		ms_lexertmp(t_minishell *ms);

// ms_parser.c
void		ms_parser(t_minishell *ms);

// ms_parsertmp.c
void		ms_parsertmp(t_minishell *ms);


#endif
