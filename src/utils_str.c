/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:20 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/13 17:03:40 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	str_close_quote(char *line, size_t *i)
{
	char	c;

	c = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != c)
	{
		(*i)++;
	}
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

char	*ft_strjoinp(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s2)
		return (ft_strdup((char *)s1));
	if (!s1)
		s1 = ft_strdup("");
	if (!s1)
		return (NULL);
	s3 = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++j])
		s3[i + j] = s2[j];
	return (s3);
}

/*
char	*ft_strjoinp(char *s1, char *s2)
{
	int 	i;
	int		j;
	char	*result;

	result = malloc(ft_strlenp(s1) + ft_strlenp(s2) + 1);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			result[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}
*/
