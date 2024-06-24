/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:45:05 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/24 11:11:35 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_parser_split
{
	size_t					i;
	size_t					start;
	int						k;
	int						dq;
	int						sq;
}	t_psplit;

typedef struct s_envl
{
	char					*key;
	char					*value;
	struct s_envl			*next;
}	t_envl;

typedef struct s_tokl
{
	char					*str;
	int						type;
	struct s_tokl			*next;
}	t_tokl;

typedef struct s_redl
{
	int						type;
	int						fdes;
	char					*path;
	char					*eof;
	struct s_redl			*next;
}	t_redl;

typedef struct s_coml
{
	char					**command;
	t_redl					*redirect;
	int						in;
	int						out;
	int						aux;
	struct s_coml			*next;
}	t_coml;

typedef struct s_strs
{
	char					*aux;
	char					*buf;
	char					*new;						
}	t_strs;

typedef struct s_ms
{
	char					*line;
	t_tokl					*token_list;
	t_coml					*cmnd_list;
	t_strs					strs;
	t_envl					*envlst;
	char					**envarr;
	int						init_fd[2];
	int						l_tubo[2];
	int						prev_fd[2];
	int						std_in;
	int						std_out;
	unsigned char			exit_code;
	int						cmnd_count;
	pid_t					pid[MAX_ARGS];
}	t_ms;

#endif
