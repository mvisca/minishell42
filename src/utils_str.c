/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:20 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/01 19:48:03 by mvisca           ###   ########.fr       */
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
