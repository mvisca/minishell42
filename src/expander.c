/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/17 18:57:12 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
expandir
${variable}
$variable
${variable:-valor_por_defecto}
${variable:+valor_por_defecto}

~:dir del usuario /home
$*:todos los parámetros
$2:segundo parámetro
$0:nombre del script
$?:código de salida
$/:número de parámetros
$!:pid del último trabajo en segundo plano

$((expresión))
$[expresión]
+ - / * % , < <= > >= == != , && || !
:precedencia de operadores, paréntesis para alterar la precedencia
:variables dentro de la expresión
:funciones matemáticas dentro de la expresión

${variables/espresión/reemplazo}
*:cualquier string
?:cualquier char
*/

/*
export v1=hola
v1
v1: command not found
$(v1)
v1:command not found

*/

static int	expander_set_values(t_expander *ex, int k, int j, t_expan_token_type token_type)
{
	ex->et[j].type = token_type;
	ex->et[i].index = j;
}

// Para cada 'command' se crea un objeto t_expander_token (con type e index)
static int	expander_tokenize(char *command, t_expander *ex)
{
	int	i;
	int	start;

	i = 0;
	while (command[i])
	{
		if (command[i] == S_QUOTE)
			str_close_quote(command, &i);
		if (command[i])
			i++;
		if (command[i] == $)
		{
			if (sq > 0 && newstr[i] == D_QUOTE)
				dq *= -1;
			if (dq > 0 && newstr[i] == S_QUOTE)
				sq *= -1;
			
			start = i;
			
		}
	}
}


void	str_close_quote(char *line, size_t *i)
{
	char	c;

	c = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != c)
		(*i)++;
}


	int		sq;
	int		dq;
	int		i;

	sq = 1;
	dq = 1;
	i = 0;
	while (str[i])
	{
		if (sq > 0 && newstr[i] == D_QUOTE)
			dq *= -1;
		if (dq > 0 && newstr[i] == S_QUOTE)
			sq *= -1;
		while (!sq && !dq && newstr[i] && newstr[i + 1] && \
			ft_isspace(newstr[i]) && ft_isspace(newstr[i + 1]))
			ft_memmove(&newstr[i + 1], &newstr[i + 2], ft_strlen(&newstr[i + 2]));
		i++;
	}

		// if (command[ex->j] == '$')
		// {
		// 	expander_set_values(ex, ex->k, ex->j, dollar);
		// 	ex->et[ex->k].type = dollar;
		// }
		// else if (command[ex->j] == '{')
		// {
		// 	ex->et[ex->k].type = curly_open;
		// }	
		// else if (command[ex->j] == '}')
		// {
		// 	ex->et[ex->k].type = curly_open;
		// }
		// else if (command[ex->j] == '(')
		// {
		// 	ex->et[ex->k].type = curve_open;
		// }
		// else if (command[ex->j] == ')')
		// {
		// 	ex->et[ex->k].type = curve_open;
		// }
		// else if (command[ex->j] == '[')
		// {
		// 	ex->et[ex->k].type = square_open;
		// }
		// else if (command[ex->j] == ']')
		// {
		// 	ex->et[ex->k].type = square_close;
		// }
		// else if (command[ex->k] != '\0')
		// {
		// 	ex->et[ex->k].type = character;
		// }
		// ex->j++;


int expander(t_ms *ms)
{
	t_expander		ex;
	int				strings;

	strings = ft_tablen(ms->cmnd_list->command);
	ex.str_num = 0;
	while (ex.str_num < strings)
		expander_tokenize(&ms->cmnd_list->command[ex.str_num++], &ex);
		// esta funcion debe iterar todo el string y buscar 

   /*
	tokenizar el comando
	0 End
	1 $ 
	2 (
	3 )
	4 {
	5 }
	6 [
	7 ]
	8 Characters

   */
	return (0);
}