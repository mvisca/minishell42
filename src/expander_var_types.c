/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:55 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/06/24 10:35:41 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expander_bad_subs(void)
{
	ft_printf("Error Bad substitution\n");
	return (1);
}

static int	expander_open_par(void)
{
	ft_printf("Error de paréntesis no cerrado\n");
	return (1);
}

int	expander_var_curly(t_ms *ms, char *str, size_t *i)
{
	size_t	start;

	if (!ft_strchr(&str[*i], '}'))
		return (expander_open_par());
	*i += 2;
	start = *i;
	while (str[*i] && (str[*i] != '}'))
	{
		if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
			return (expander_bad_subs());
		(*i)++;
	}
	ms->strs.aux = ft_substr(str, start, (&str[*i] - &str[start]));
	*i += 1;
	if (!ms->strs.aux || ft_strlen(ms->strs.aux) == 0)
		return (expander_bad_subs());
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
int	expander_var_alpha(t_ms *ms, char *str, size_t *i)
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
int	expander_var_exit(t_ms *ms, char *str, size_t *i)
{
	if (ft_strnstr(str, "$?", 2))
		*i += 2;
	else if (ft_strnstr(str, "${?}", 4))
		*i += 4;
	ms->strs.buf = ft_itoa(ms->exit_code);
	return (0);
}
