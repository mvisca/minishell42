/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:59:09 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/04 22:57:59 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parser_free_all(char **spliter)
{
	int	i;

	i = 0;
	while (spliter[i])
	{
		free(spliter[i]);
		i++;
	}
	free(spliter);
}

static int	parser_count(const char *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == S_QUOTE || s[i] == D_QUOTE)
		{
			if (i == 0 || s[i -1] == c)
				count++;
			str_close_quote((char *)s, &i);
			i++;
		}
		if (s[i] && s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		if (s[i])
			i++;
	}
	return (count);
}

static char	**parser_do_split(char **spliter, const char *s, char c)
{
	size_t	i;
	int		k;
	int		start;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if (s[i] == S_QUOTE || s[i] == D_QUOTE)
			str_close_quote((char *)s, &i);
		if (s[i] && s[i] != c && (s[i + 1] == c || !s[i + 1]))
		{
			spliter[k] = ft_substr(s, start, i + 1 - start);
			if (!spliter[k++])
			{
				parser_free_all(spliter);
				return (NULL);
			}
		}
		if (s[i])
			i++;
	}
	spliter[k] = NULL;
	return (spliter);
}

char	**parser_split(char *str)
{
	char	**tab;
	int		count;

	if (!str)
		return (NULL);
	count = parser_count(str, 32);
	tab = malloc (sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab = parser_do_split(tab, str, 32);
	if (!tab)
		return (NULL);
	return (tab);
} 

// hola "hola hola" -> hola
// hola "esto es junto" y esto no | y esto"si que es"junto