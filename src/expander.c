/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/23 19:07:53 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// extracts var name and gets value when between curly brakets
// NO HAY QUE MANEJAR PARÉNTESIS NO CERRADO
static char	*expander_var_curly(t_ms *ms, char *str, size_t *i)
{
	unsigned int	start;
	char			*aux;
	char			*buf;	

	if (!ft_strchr(&str[*i], '}'))
	{
		ft_printf("Error de paréntesis no cerrado\n");
		return (NULL);
	}
	start = *i + 2;
	while (str[*i] && (str[*i] != '}'))
	{
		if (!ft_isalnum(str[*i]) || str[*i] != '_')
		{
			ft_printf("Error Bad sustitution\n");
			return (NULL);
		}	
		*i += 1;
	}
	aux = ft_substr(str, start, (&str[*i] - &str[start]));
	*i += 1;
	if (!aux)
	{
		ft_printf("Error de mala substitución");
		return (NULL);
	}
	buf = environment_get_value(ms, aux);
	free(aux);
	buf = ft_strdup(buf);
	return (buf);
}

// extracts var name and gets value when not between curly brakets
static char	*expander_var_alpha(t_ms *ms, char *str, size_t *i) 
{
	unsigned int	start;
	char			*aux;
	char			*buf;

	*i += 1;
	start = *i;
	while (str[*i] && ft_isalnum(str[*i]))
		*i += 1;
	aux = ft_substr(str, start, (&str[*i] - &str[start]));
	buf = environment_get_value(ms, aux);
	free(aux);
	if (!buf)
		buf = ft_strdup("\n");
	else
		buf = ft_strdup(buf);
	return (buf);
}

// retrives exit code
static char	*expander_var_exit(t_ms *ms, char *str, size_t *i)
{
	char	*buf;

	if (ft_strnstr(str, "$?", 2))
		*i += 2;
	else if (ft_strnstr(str, "${?}", 4))
		*i += 4;
	buf = ft_itoa(ms->exit_code);
	return (buf);
}

static char	*expander_get_expansion(t_ms *ms, char *str)
{
	char	*aux;
	char	*buf;
	char	*new;
	size_t	i;

	i = 0;
	new = NULL;
	buf = NULL;
	aux = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			str_close_quote(str, &i);
		else if (ft_strnstr(&str[i], "$?", 2) || ft_strnstr(&str[i], "${?}", 4))
			buf = expander_var_exit(ms, str, &i);
		else if (str[i] == '$' && str[i + 1] == '{')
			buf = expander_var_curly(ms, str, &i);
		else if (str[i] == '$' && ft_isalnum(str[i + 1]))
			buf = expander_var_alpha(ms, str, &i);
		else
			buf = ft_substr(str, i++, 1);
		ft_printf(RED"i = %d\n"RESET, i);
		ft_printf(RED"last char = %c\n"RESET, str[i]);
		if (!buf)
		{
			ft_printf("SALE AQUI\n");
			return (NULL);
		}
		aux = new;
		new = ft_strjoin(aux, buf);
		free(buf);
		free(aux);
	}
	ft_printf("new %s\n", new);
	return (new);
}

int	expander(t_ms *ms)
{
	int			i;
	char		*aux;
	t_coml		*node;

	node = ms->cmnd_list;
	while (node)
	{
		i = 0;
		while (node && node->command && node->command[i])
		{
			if (ft_strchr(node->command[i++], '$'))
			{
				aux = expander_get_expansion(ms, node->command[i-1]);
				if (!aux)
				{
					ft_printf("Error break");
					return (1);
				}
				free(node->command[i-1]);
				node->command[i-1] = aux;
			}
		}
		node = node->next;
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