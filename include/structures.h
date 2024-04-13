/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:45:05 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/13 21:01:08 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

//variable global para gestionar las senyales.
extern	int	g_exit;

typedef struct s_parser_split
{
	size_t					i;
	size_t					start;
	int						k;
	int						dq;
	int						sq;
} 	t_psplit;

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
	struct s_redl			*next;
} t_redl;

typedef struct s_coml
{
	char					**command; // command[0] = comando; command[1] = opciones... command[n] = NULL;
	t_redl					*redirect; // NULL o VALIDO
	int						in;//control entrada para dups 
	int						out;//control salida para dups
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
	t_coml					*cmnd_list_fake;
	t_strs					strs;
	t_envl					*envlst;
	char					**envarr;
	int						init_fd[2];//dup inicial de STDIN y STDOUT
	int						tubo[2];//la pipe (prescinidible)
	int						prev_fd[2];//prescindible
	int						exit_code;
	int						cmnd_count; // remplazar ms->debug->cmnd_count
	pid_t					pid;//para controlar executor
}	t_ms;

#endif
