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
t_envlst	*environment_init(t_minishell *ms);
t_envlst	*environment_new_node(t_minishell *ms, char *key, char *value);
t_envlst	*environment_add_node(t_minishell *ms, t_envlst *envnode);
t_envlst	*environment_get_node(t_minishell *ms, char *key);
char		*environment_get_value(t_minishell *ms, char *key);
void		environment_del_node(t_minishell *ms, char *key);

/*##################	ERRORS		#####################*/
// System errors
void		error_exit(char *msj, t_minishell *ms);
void		error_free_exit(char *msj, t_minishell *ms);
// User errors
int			errors_syntax(t_minishell *ms);
int         errors_syntax_curly_brackets(char *line);

/*##################	EXECUTOR	#####################*/

/*##################	EXPANSOR	#####################*/

/*##################	INITIALIZER	#####################*/
void		initialize(t_minishell *ms, int ac, char **av, char **envp);

/*##################	INTERFACE	#####################*/
void		interface_get_line(t_minishell *ms);

/*##################	LEXER		#####################*/

/*##################	PARSER		#####################*/

/*##################	UTILS		#####################*/
void		utils_free_str(char *str);
void		utils_free_tab(char **tab);
void		utils_free_env_list(t_envlst *env);
void		utils_free_token_list(t_tokenlst *env);
void		utils_free_comnd_list(t_comndlst *env);
void		utils_free_ms(t_minishell *ms);
int         utils_skip_spaces(char *str, int i);

#endif
