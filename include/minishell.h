/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:44:33 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/08 01:07:37 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <dirent.h>

# include "global.h"
# include "macros.h"
# include "structures.h"
# include "../lib/libft/include/libft.h"

/*##################	BUILTINS	#####################*/

int         builtin_echo(char **com);

/*##################	DEBUG		#####################*/

int         debug_all(t_ms *ms, int env, int tok, int com);
void        debug_token(t_ms *ms);
void        debug_command(t_ms *ms);
void        debug_envarr(t_ms *ms);
void	    debug_expand(t_ms *ms);

/*##################	ENVIRONMENT	#####################*/

// Factory
t_envl      *environment_init(t_ms *ms, char **envp);
t_envl      *environment_new_node(t_ms *ms, char *key, char *value);
t_envl      *environment_add_node(t_ms *ms, t_envl *envnode);
void		environment_del_node(t_ms *ms, char *key);
void        environment_update_node(t_ms *ms, char *key, char *value);

// Getters
t_envl      *environment_get_node(t_ms *ms, char *key);
char		*environment_get_value(t_ms *ms, char *key);

/*##################	ERRORS		#####################*/

// System errors
void		error_exit(char *msj, t_ms *ms);
void		error_free_exit(char *msj, t_ms *ms);
void		ft_error_exit(char *com, char *msj, int code);

// User errors
int			errors_syntax(t_ms *ms);
int	        errors_syntax_display(t_ms *ms, char *str);

// Sybtax error cases
int         errors_pipe(t_ms *ms, t_tokl *token);
int         errors_redir(t_ms *ms, t_tokl *token);
int         errors_word(t_ms *ms, t_tokl *token);
int         errors_start(t_ms *ms);

/*##################	EXECUTOR	#####################*/

int			ft_execute(t_ms *ms);

/*##################	EXPANDER	#####################*/

int			expander(t_ms *ms);
char        *expander_filter_quotes(char *str);

/*##################	INITIALIZER	#####################*/

void		initialize(t_ms *ms, int ac, char **av, char **envp);

/*##################	INTERFACE	#####################*/

int	    	interface_get_line(t_ms *ms);
int	        empty_exit(t_ms *ms);


/*##################	LEXER		#####################*/

int			lexer(t_ms *ms, char *line);
int			lexer_make_token(t_ms *ms, char *line, int type, int *i);
char		*lexer_make_token_str(char *line);
t_tokl	    *lexer_add_token(t_ms *ms, t_tokl *token);

/*##################	PARSER		#####################*/

int			parser(t_ms *ms);
t_coml		*parser_new_command(t_coml **commnad);
int			parser_add_command(t_ms *ms, t_coml *command);
char        **parser_split(char *str);
void        parser_ps_init(t_psplit *ps);

int			parser_add_redirect(t_coml *cmnd, t_redl *redir);
int         parser_update_envarr(t_ms *ms);

/*##################	SIGNAL		#####################*/

int	        signal_init(int mode);
int         signal_ignore(int sig_type);

/*##################	UTILS		#####################*/

// Memory
int 		utils_free_ms(t_ms *ms, int clean_env);
void		utils_free_tab(char ***tab);
void		utils_free_env_list(t_envl **env);
void		utils_free_token_list(t_tokl **token);
void		utils_free_cmnd_list(t_coml **cmnd);

// String
size_t      str_line_len(char *line);
void        str_close_quote(char *line, size_t *i);

#endif
