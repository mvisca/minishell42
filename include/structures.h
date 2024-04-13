/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:45:05 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/13 16:55:07 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// extern	int	g_sig; //variable global para gestionar las senyales.
// Podria ser una estructura si conviniera

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
	int						in;//control entrada para dups sera un fd
	int						out;//control salida para dups sera un fd
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
	int						l_tubo[2];//la pipe del proceso
	int						prev_fd[2];//0
	int						exit_code;
	int						cmnd_count;
	pid_t					pid[MAX_ARGS];//para controlar executor y funcion espera
}	t_ms;

#endif
