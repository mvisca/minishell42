/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:59:09 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/22 05:20:28 by mvisca-g         ###   ########.fr       */
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
			if (i == 0 || s[i -1] == c || s[i -1] == '\n')
				count++;
			str_close_quote((char *)s, &i);
			if (s[i])
				i++;
		}
		if (s[i] && s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		if (s[i])
			i++;
	}
	return (count);
}

static char	**parser_do_split(char **aux_tab, const char *s, char c, int k)
{
	size_t	i;
	int		start;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if ((s[i] == S_QUOTE || s[i] == D_QUOTE) && s[i + 1])
			str_close_quote((char *)s, &i);
		if (s[i] && s[i] != c && (s[i + 1] == c || !s[i + 1]))
		{
			aux_tab[k] = ft_substr(s, start, i + 1 - start);
			if (!aux_tab[k++])
			{
				parser_free_all(aux_tab);
				return (NULL);
			}
		}
		if (s[i])
			i++;
	}
	aux_tab[k] = NULL;
	return (aux_tab);
}

char	**parser_split(char *str)
{
	int		count;
	char	**aux_tab;

	if (!str)
		return (NULL);
	count = parser_count(str, 32);
	aux_tab = ft_calloc(sizeof(char *), (count + 2));
	if (!aux_tab)
		return (NULL);
	aux_tab = parser_do_split(aux_tab, str, 32, 0);
	if (!aux_tab)
		return (NULL);
	return (aux_tab);
}
