/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/21 15:39:42 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expander_init_strs(char ***strs, int alloc_str)
{
	*strs = (char **)ft_calloc(3, sizeof(char *));
	if (!*strs)
		return (1);
	if (alloc_str)
	{
		(*strs)[NEW] = ft_strdup("");
		if (!(*strs)[NEW])
		{
			free(*strs);
			return (1);
		}
	}
	return (0);
}

static int	expander_var(t_ms *ms, char *str, int *i, char **strs) // coger hasta que se cierra el curly // BUF devuelve
{
	unsigned int	start;

	if (str[*i] == '?')
	{
		strs[BUF] = ft_itoa(ms->exit_code);
		(*i)++;
		return (*i);
	}
	else
	{
		start = *i;
		while (str[*i] && str[*i] != C_CURLY)
			(*i)++;
		if (str[*i] == '\0')
			return (*i);
		strs[AUX] = ft_substr(str, start, (size_t)(&str[*i] - &str[start])); // es el nombre de la variable
		strs[BUF] = environment_get_value(ms, strs[AUX]); // es el valor, no se libera aquí, será reemplazado despues
		free(strs[AUX]);
	}
	return (0);
}

static char	*expander_get_expansion(t_ms *ms, char *str) //, t_deb_exp deb_exp)
{
	char	**strs;
	int		i;

	if (expander_init_strs(&strs, TRUE) != 0) // strs[NEW] es ""
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR && str[i+1] == O_CURLY) // bloque // aquí modificar el strs[SWITCH] y llamar
			i += 2;
		else if (str[i] == DOLLAR && (ft_isalpha(str[i+1]) || str[i+1] == '?')) // bloque
			i++;
		if (str[i] == O_CURLY || ft_isalpha(str[i]) || str[i] == '?')
			expander_var(ms, str, &i, strs); //, deb_exp); // coger hasta que se cierra el curly // DEB quitar despues
		else // uno a uno
			strs[BUF] = ft_substr(str, i++, 1); // coge uno

		strs[AUX] = strs[NEW];
		strs[NEW] = ft_strjoin(strs[AUX], strs[BUF]);
		if (str[BUF])
			free(strs[BUF]);
		free(strs[AUX]);
	}
	return (strs[NEW]);
}

int	expander(t_ms *ms)
{
	int			i;
	char		**strs;

	if (expander_init_strs(&strs, FALSE) != 0)
		return (1);
	i = 0;
	while (ms->cmnd_list && ms->cmnd_list->command[i])
	{
		if (ft_strchr(ms->cmnd_list->command[i], DOLLAR))
		{
			strs[NEW] = expander_get_expansion(ms, ms->cmnd_list->command[i]); //, deb_exp); // DEB deb_exp should be removed after debug
			free(ms->cmnd_list->command[i]);
			ms->cmnd_list->command[i] = strs[NEW];
		}
		i++;
	}
	free(strs);
	return (0);
}

/*
expandir
${variable}
$variable
${variable:-valor_por_defecto}
${variable:+valor_por_defecto}

~:dir del usuario /home
$*:todos los parámetros ?? QUE ES ESTO
$2:segundo parámetro ?? QUE ES ESTO
$0:nombre del script ?? QUE ES ESTO
$?:código de salida OK
$/:número de parámetros ?? QUE ES ESTO
$!:pid del último trabajo en segundo plano ?? QUE ES ESTO

$((expresión)) - NOT HADLED
$[expresión] - NOT HANDLED
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