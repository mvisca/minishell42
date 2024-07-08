/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:55 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/07/08 17:27:22 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	expander_bad_subs(t_ms *ms)
{
	ft_putstr_fd("error: bad substitution\n", 2);
	ms->exit_code = 2;
	ms->syntax_errors = 1;
	return (1);
}

static int	expander_open_par(t_ms *ms, size_t *i)
{
	ft_putstr_fd("error: parentheses mismatch not handled by minishell\n", 2);
	ms->exit_code = 2;
	(*i)++;
	ms->syntax_errors = 1;
	return (1);
}

int	expander_var_curly(t_ms *ms, char *str, size_t *i)
{
	size_t	start;

	if (!ft_strchr(&str[*i], '}'))
		return (expander_open_par(ms, i));
	*i += 2;
	start = *i;
	while (str[*i] && (str[*i] != '}'))
	{
		if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
			return (expander_bad_subs(ms));
		(*i)++;
	}
	ms->strs.aux = ft_substr(str, start, (&str[*i] - &str[start]));
	*i += 1;
	if (!ms->strs.aux || ft_strlen(ms->strs.aux) == 0)
		return (expander_bad_subs(ms));
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
