/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:20 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/01 12:20:54 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	str_close_quote(t_ms *ms, char *line, size_t *i)
{
	char	c;
	size_t	j;

	j = *i;
	if (line && *i < ft_strlen(line) && !ft_strchr(&line[*i], line[*i]))
		return (errors_syntax_display(ms, "error: parenthesys missmatch"));
	if (line && line[*i])
	{
		c = line[*i];
		(*i)++;
		while (line && *i < ft_strlen(line) && line[*i] && line[*i] != c)
		{
			(*i)++;
		}
	}
	if (!line[*i])
		*i = j;
	return (0);
}

size_t	str_line_len(t_ms *ms, char *line)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
	{
		flag = 0;
		if (line[i] == S_QUOTE || line[i] == D_QUOTE)
		{
			str_close_quote(ms, line, &i);
			if (line[i])
				i++;
			flag = 1;
		}
		if (!flag)
			i++;
	}
	return (i);
}

void	strs_reset(t_ms *ms)
{
	ms->strs.aux = NULL;
	ms->strs.buf = NULL;
	ms->strs.new = NULL;
}

int	strs_free(t_ms *ms)
{
	if (ms->strs.aux)
		free(ms->strs.aux);
	if (ms->strs.buf)
		free(ms->strs.buf);
	if (ms->strs.new)
		free(ms->strs.new);
	strs_reset(ms);
	return (0);
}
