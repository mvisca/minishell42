/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/17 23:59:36 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expander_var_name(t_ms *ms, size_t i, size_t *j)
{
	// tiene el punto de partida de ms->cmnd_list->command[i][j]
	// mientras que no sea D_QUOTE or '\0' or !ft_isalnum
		// junta el nombre de la variable
	// con el nombre de la variabla la busca
		// si encuentra suistituye el valor en el string
		// si no la encuentra es nada
	return (0);
}

static int	expander_in_d_quote(t_ms *ms, size_t i, size_t *j)
{
	char	*str;
	char	*start;

	str = ms->cmnd_list->command[i];
	start = ft_strchr(str, DOLLAR);
	if (!start)
		str_close_quote(str, j); // j es puntero
	else
		expander_var_name(ms, i, j); // j es puntero


	// itera por str
	// busca $ o EOF o "

	return (0);
}

int expander(t_ms *ms)
{
	size_t	i;
	size_t	j;
	int		count;
	char	*str;

	i = 0;
	count = ft_tablen(ms->cmnd_list->command);
	while (ms->cmnd_list && ms->cmnd_list->command && ms->cmnd_list->command[i])
	{
		str = &ms->cmnd_list->command[i];
		j = 0;
		while (str[j])
		{
			if (str[j] == S_QUOTE)
				str_close_quote(str[j], (size_t *)&j);
			else if (str[j] == D_QUOTE)
				expander_in_d_quote(ms, i, &j);
			else if (str[j] == DOLLAR)
				expander_var_name(ms, i, &j); // '\0' '"' !alphanum 
			if (ms->cmnd_list->command[i][j])
				j++;
		}
		i++;
	}
	return (0);
}

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