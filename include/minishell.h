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
t_envl	*environment_init(t_ms *ms, char **envp);
t_envl	*environment_new_node(t_ms *ms, char *key, char *value);
t_envl	*environment_add_node(t_ms *ms, t_envl *envnode);
t_envl	*environment_get_node(t_ms *ms, char *key);
char		*environment_get_value(t_ms *ms, char *key);
void		environment_del_node(t_ms *ms, char *key);

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
void		interface_get_line(t_ms *ms);

/*##################	LEXER		#####################*/
int			lexer(t_ms *ms, char *line);
t_tokl	    *add_token(t_ms *ms, t_tokl *token);
char		*make_token_word(char *line);
int			make_token(t_ms *ms, char *line, int type);
int			lexer_clean(t_ms *ms);

/*##################	PARSER		#####################*/
int			parser(t_ms *ms);
int			make_comnd_node(t_ms *ms, t_tokl *s, t_tokl *e);
t_tokl		*find_end(t_tokl *start);


/*##################	UTILS		#####################*/
void		free_tab(char **tab);
void		free_env_list(t_envl *env);
void		free_token_list(t_tokl *env);
void		free_comnd_list(t_coml *env);
int 		free_ms(t_ms *ms);

char        *str_clean_spaces(char *str);

int			array_alloc(t_coml *c, t_tokl *s, t_tokl *e);
int			array_append(t_coml *comnd, t_tokl *s, t_tokl *e);


#endif
