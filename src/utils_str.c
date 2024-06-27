/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:20 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/27 22:05:16 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	str_close_quote(char *line, size_t *i)
{
	char	c;
	size_t	j;

	j = *i;
	ft_printf("in\n");
	if (line && line[*i])
	{
		c = line[*i];
		ft_printf("c= %c\n", c);
		(*i)++;
		while (line && line[*i] && line[*i] != c)
		{
			ft_printf("char = %c %d ", line[*i], *i);
			(*i)++;
		}
		ft_printf("\n");
	}
	if (!line[*i])
		*i = j + 1;
}

size_t	str_line_len(char *line)
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
			str_close_quote(line, &i);
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
