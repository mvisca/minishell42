/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/20 14:15:46 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expander_init_strs(char ***strs)
{
	*strs = (char **)ft_calloc(3, sizeof(char *));
	if (!*strs)
		return (1);
	(*strs)[NEW] = ft_strdup("");
	if (!(*strs)[NEW])
	{
		free(*strs);
		return (1);
	}
	return (NEW);
}

static char	*expander_get_expansion(char *str)
{
	char	**strs;

	if (expander_init_strs(&strs) != 0)
		return (1);
	strs[NEW] = str;
	while (str)
	{
		// copiar char por char
		// si es DOLLAR hacer esto
		str = ft_strchr(str, DOLLAR);
		if (*(str + 1) == CURLY_OPEN || ft_isalpha(*(str + 1)))
		{
			
		}
		else
		{
			strs[AUX] = strs[NEW];
			strs[NEW] = ft_strjoin(strs[AUX], "$");
			free(strs[AUX]);
			str++;
		}
	}
	return (strs[NEW]);
}

int	expander(t_ms *ms)
{
	int		i;
	char	**strs;
	// NEW AUX BUF

	if (expander_init_strs(&strs) != 0)
		return (1);
	free(strs[NEW]);
	i = 0;
	while (ms->cmnd_list && ms->cmnd_list->command[i])
	{
		if (ft_strchr(ms->cmnd_list->command[i], DOLLAR))
		{
			strs[AUX] = ms->cmnd_list->command[i];
			strs[NEW] = expander_get_expansion(ms->cmnd_list->command[i]);
			ms->cmnd_list->command[i] = strs[NEW];
			free(strs[AUX]);
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