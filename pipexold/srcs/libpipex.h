/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:24:27 by fcatala-          #+#    #+#             */
/*   Updated: 2023/06/06 08:43:48 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include "../libft/libft.h"

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"
# define R_END 0
# define W_END 1
# define H_FILE ".xyz_here_tmp" 
# define IN_FILE 0
# define OUT_FILE 1
# define HERE_DOC 2
# define MSG_0 "Oh fi##k! Unexpected error"
# define MSG_1 "Wrong number of arguments. Please check documentation or input"
# define MSG_2 "No such file or directory"
# define MSG_3 "Unable to generate outfile"
# define MSG_4 "Error in dup infile"
# define MSG_5 "Je n'aime pas les pipes ;-P"
# define MSG_6 "Unable to fork"
# define MSG_7 ": command not found\n"
# define MSG_8 "here_doc management is not included in manadatory"

int		ft_error(char *msg, int err);
int		ft_err_m(char *msg, int err);
int		ft_openfile(char *file, int mode, char *infile);
int		ft_here_doc(char **argv);
int		ft_end_quote(char *aux, int i, char tmp);
char	**ft_split_cmd(char *argv);
char	**get_cmd(char *argv, char **envp);
void	run_cmd(char *argv, char **envp, int fd_file, int ctr);
void	run_child_1(char **argv, char **envp, int *fd_file, int *ctr);
void	run_child_end(char **argv, char **envp, int *fd_file, int argc);
#endif
