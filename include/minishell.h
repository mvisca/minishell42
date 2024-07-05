/* ************************************************************************** */
/*			                      */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:44:33 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/05 11:59:00 by fcatala-         ###   ########.fr       */
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

int				builtin_cd(t_ms *ms, char **path, int i);
int				builtin_echo(char **com);
unsigned char	builtin_exit(t_ms *ms, char **cmnd);
int				builtin_export(t_ms *ms, t_coml *cmnd);
int				export_context(t_ms *ms, t_coml *cmnd, int i, int j);
int				export_context_expand(t_ms *ms, t_coml *cmnd, int i, int j);
int				export_context_error(t_ms *ms, char *key);
int				export_error(char *command);
void			export_ff(int *j, char *line);
void			export_concat(t_ms *ms, int j, char *line);
void			export_assign(t_ms *ms, int j, char *line);
int				export_solo(t_ms *ms, char *line);
void			export_get_key_value(int j, char *line, char **key, char **v);
int				export_no_options(t_coml *comnd);
int				export_print_env(t_ms *ms);
int				builtin_pwd(t_ms *ms);
int				builtin_unset(t_ms *ms, t_coml *cmnd);
int				ft_builtin_redir(t_coml *job);

/*##################	DEBUG		#####################*/

int				debug_all(t_ms *ms, int env, int tok, int com);
void			debug_token(t_ms *ms);
void			debug_command(t_ms *ms);
void			debug_envarr(t_ms *ms);
void			debug_tab(char **tab);

//void			debug_expand(t_ms *ms);

/*##################	ENVIRONMENT	#####################*/

// Factory
t_envl			*environment_init(t_ms *ms, char **envp);
t_envl			*environment_new_node(t_ms *ms, char *key, char *value);
t_envl			*environment_add_node(t_ms *ms, t_envl *envnode);
void			environment_del_node(t_ms *ms, char *key);
void			environment_update_node(t_ms *ms, char *key, char *value);
void			environment_sort(t_envl **env);

// Getters
t_envl			*environment_get_node(t_ms *ms, char *key);
char			*environment_get_value(t_ms *ms, char *key);

/*##################	ERRORS		#####################*/

// System errors
void			error_exit(char *msj, t_ms *ms);
void			error_free_exit(char *msj, t_ms *ms);
void			ft_error_exit(char *com, char *msj, int code);
void			ft_error_noexit(char *com, char *path, char *msj);
int				ft_error_return(char *com, char *path, char *msj, int code);

// User errors
int				errors_syntax(t_ms *ms);
int				errors_syntax_display(t_ms *ms, char *str);

// Sybtax error cases
int				errors_pipe(t_ms *ms, t_tokl *token);
int				errors_redir(t_ms *ms, t_tokl *token);
int				errors_word(t_ms *ms, t_tokl *token);
int				errors_start(t_ms *ms);

/*##################	EXECUTOR	#####################*/

int				ft_execute(t_ms *ms);

/*##################	EXECUTOR FILES & REDIRS  #####################*/

int				ft_openfile(char *file, int redir);
int				ft_closer(t_ms *ms, int i);
void			ft_redirin(t_redl	*files, int last);
void			ft_redirout(t_coml *job, int last);

/*##################	EXECUTOR UTILS 1 & 2  #####################*/

int				ft_countcmd(t_coml *coml);
char			*ft_getcmd(char *cmnd, t_ms *ms, int last);
int				ft_isdir(char *path);
void			ft_dup_close(int tubo[2], int pos, int out);
void			ft_reset_dups(t_ms *ms);
int				ft_is_builtin(t_coml *aux);
int				builtin_env(t_ms *ms);
int				ft_execute_built(t_coml *aux, t_ms *ms, int type);
void			ft_waitend(pid_t pid, t_ms *ms);
void			ft_wait(int count, pid_t pid[MAX_ARGS]);

/*##################	EXPANDER	#####################*/

int				expander(t_ms *ms);
char			*expander_filter_quotes(char *str);
int				expander_get_expansion(t_ms *ms, char *str, size_t i);
int				expander_var_exit(t_ms *ms, char *str, size_t *i);
int				expander_var_alpha(t_ms *ms, char *str, size_t *i);
int				expander_var_curly(t_ms *ms, char *str, size_t *i);

/*##################	EXTEND LIBFT	#####################*/

int				ft_isspace(char c);
int				ft_tablen(char **tab);

/*##################	HEREDOC			#####################*/

int				ft_search_hd(t_ms *ms, t_coml *job);

/*##################	INITIALIZER	#####################*/

void			initialize(t_ms *ms, int ac, char **av, char **envp);

/*##################	INTERFACE	#####################*/

int				interface_get_line(t_ms *ms);
int				empty_exit(t_ms *ms);

/*##################	LEXER		#####################*/

int				lexer(t_ms *ms, char *line);
int				lexer_make_token(t_ms *ms, char *line, int type, int *i);
char			*lexer_make_token_str(char *line);
t_tokl			*lexer_add_token(t_ms *ms, t_tokl *token);

/*##################	PARSER		#####################*/

int				parser(t_ms *ms);
t_coml			*parser_new_command(t_coml **commnad);
int				parser_add_command(t_ms *ms, t_coml *command);
char			**parser_split(char *str);
void			parser_ps_init(t_psplit *ps);

int				parser_add_redirect(t_coml *cmnd, t_redl *redir);
int				parser_update_envarr(t_ms *ms, int i, int node_num);

/*##################	SIGNAL		#####################*/

int				signal_init(int mode);
int				signal_ignore(int sig_type);
void			heredoc_handler(int signum);
void			interactive_handler(int signum);
void			normal_handler(int signum);
int				ft_event_hook(void);
int				ft_event_hook2(void);

/*##################	UTILS		#####################*/

// Memory
int				utils_free_ms(t_ms *ms, int clean_env);
void			utils_free_tab(char ***tab);
void			utils_free_env_list(t_envl **env);
void			utils_free_token_list(t_tokl **token);
void			utils_free_cmnd_list(t_coml **cmnd);

// String
size_t			str_line_len(char *line);
void			str_close_quote(char *line, size_t *i);
void			strs_reset(t_ms *ms);
int				strs_free(t_ms *ms);

/*##################	UTILS2_STR		#####################*/

int				ft_strcmp(const char *s1, const char *s2);
int				ft_strlenp(const char *str);
char			*ft_strcat(char *dest, const char *add);
char			*ft_strjoin3(char *str1, char *str2, char *str3);
int				ft_is_quoted(char *eof);
//char			*ft_strlwr(char *str);//not used

/*##################	UTILS3_STR		#####################*/
void			ft_freechain(char **chain);
void			*ft_memdel(void *ptr);
void			ft_free_nullify(char **ptr);

#endif
