/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:45:05 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/11 17:36:46 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

//variable global para gestionar las senyales.
//extern	int	g_exit;

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
	char					*eof;//NUEVO para controlar el hd
	struct s_redl			*next;
}  t_redl;

typedef struct s_coml
{
	char					**command; // command[0] = comando; command[1] = opciones... command[n] = NULL;
	t_redl					*redirect; // NULL o VALIDO
	int						in;//control entrada para dups sera un fd
	int						out;//control salida para dups sera un fd
	int						aux;//control para saltarse la ejecucion del comando
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
	int						init_fd[2];//dup inicial de STDIN y STDOUT
	int						l_tubo[2];//la pipe del proceso
	int						prev_fd[2];//no se usa
	int						std_in;//dup inicial STDIN 
	int						std_out;//dup inicial STDOUT
	int						exit_code;
	int						cmnd_count;
//	int						hdl;//control de las lineas escritas en heredoc
//	pid_t					pid;
	pid_t					pid[MAX_ARGS];//para controlar executor y funcion espera
}	t_ms;

#endif
