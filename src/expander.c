/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/25 20:06:27 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// extracts var name and gets value when between curly brakets
// NO HAY QUE MANEJAR PARÉNTESIS NO CERRADO
static int	expander_var_curly(t_ms *ms, char *str, size_t *i)
{
	unsigned int	start;

	if (!ft_strchr(&str[*i], '}'))
	{
		ft_printf("Error de paréntesis no cerrado\n");
		return (1);
	}
	start = *i + 2;
	while (str[*i] && (str[*i] != '}'))
	{
		if (!ft_isalnum(str[*i]) && str[*i] != '_')
		{
			ft_printf("Error Bad substitution 1\n");
			return (1);
		}	
		*i += 1;
	}
	ms->strs.aux = ft_substr(str, start, (&str[*i] - &str[start]));
	*i += 1;
	if (!ft_strlen(ms->strs.aux))
	{
		ft_printf("Error Bad substitution 2\n");
		return (1);
	}
	ms->strs.buf = environment_get_value(ms, ms->strs.aux);
	free(ms->strs.aux);
	ms->strs.aux = NULL;
	if (!ms->strs.buf)
		ms->strs.buf = ft_strdup("\n");
	else
		ms->strs.buf = ft_strdup(ms->strs.buf);
	return (0);
}

// extracts var name and gets value when not between curly brakets
static int	expander_var_alpha(t_ms *ms, char *str, size_t *i) 
{
	unsigned int	start;

	*i += 1;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	ms->strs.aux = ft_substr(str, start, (&str[*i] - &str[start]));
	ms->strs.buf = environment_get_value(ms, ms->strs.aux);
	free(ms->strs.aux);
	ms->strs.aux = NULL;
	if (!ms->strs.buf)
		ms->strs.buf = ft_strdup("\n");
	else
		ms->strs.buf = ft_strdup(ms->strs.buf);
	return (0);
}

// retrives exit code
static int	expander_var_exit(t_ms *ms, char *str, size_t *i)
{
	if (ft_strnstr(str, "$?", 2))
		*i += 2;
	else if (ft_strnstr(str, "${?}", 4))
		*i += 4;
	ms->strs.buf = ft_itoa(ms->exit_code);
	return (0);
}

static int	expander_get_expansion(t_ms *ms, char *str)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE)
		{
			start = i;
			str_close_quote(&str[i], &i);
			ms->strs.buf = ft_substr(str, start, i - start + 1);
			i++;

		}
		else if (ft_strnstr(&str[i], "$?", 2) || ft_strnstr(&str[i], "${?}", 4))
			expander_var_exit(ms, str, &i);
		else if (str[i] == '$' && str[i + 1] == '{')
			expander_var_curly(ms, str, &i); // escribe en ms->strs.buf
		else if (str[i] == '$' && ft_isalpha(str[i + 1]))
			expander_var_alpha(ms, str, &i); // escribe en ms->strs.buf
		else
			ms->strs.buf = ft_substr(str, i++, 1);
		if (!ms->strs.buf)
		{
			ft_printf("System o syntax Error\n");
			return (1);
		}
		ms->strs.aux= ms->strs.new;
		ms->strs.new = ft_strjoin(ms->strs.aux, ms->strs.buf);
		free(ms->strs.buf);	
		ms->strs.buf = NULL;
		free(ms->strs.aux);
	}
	return (0);
}

int	expander(t_ms *ms)
{
	int			i;
	t_coml		*node;

	node = ms->cmnd_list;
	while (node)
	{
		i = 0;
		while (node->command && node->command[i])
		{
			expander_get_expansion(ms, node->command[i]);
			ft_printf("address de strs %p y strs.new %p\n", ms->strs, ms->strs.new);
			if (!ms->strs.new)
			{
				ft_printf("Error break\n");
				return (1);
			}
			free(node->command[i]); // viene cambiado o vacío?
			node->command[i] = ms->strs.new;
			ms->strs.new = NULL;
			i++;
		}
		node = node->next;
	}
	return (0);
}
