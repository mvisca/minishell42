/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:20 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 21:17:50 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	str_close_quote(char *line, size_t *i)
{
	char	c;

	c = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != c)
		(*i)++;
}

size_t	str_line_len(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == S_QUOTE || line[i] == D_QUOTE)
			str_close_quote(line, &i);
		i++;
	}
	return (i);
}


















char	*str_clean_spaces(char *str)
{
	char	*newstr;
	int		sq;
	int		dq;
	int		i;

	sq = 1;
	dq = 1;
	i = 0;
	newstr = ft_strtrim(str, " \t");
	while (newstr[i])
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
	return (newstr);
}

int	str_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}
