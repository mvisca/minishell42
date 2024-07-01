/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:59:09 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/01 12:22:29 by mvisca           ###   ########.fr       */
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

static int	parser_count(t_ms *ms, const char *s, char c)
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
			str_close_quote(ms, (char *)s, &i);
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

static char	**parser_do_split(t_ms *ms, const char *s, char c, int k)
{
	size_t	i;
	int		start;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		ft_printf("%s\n", &s[i]);
		if ((s[i] == S_QUOTE || s[i] == D_QUOTE) && s[i + 1])
			str_close_quote(ms, (char *)s, &i);
		if (s[i] && s[i] != c && (s[i + 1] == c || !s[i + 1]))
		{
			ms->aux_tab[k] = ft_substr(s, start, i + 1 - start); // i + 1 - start
			if (!ms->aux_tab[k++])
			{
				parser_free_all(ms->aux_tab);
				return (NULL);
			}
		}
		if (s[i])
			i++;
	}
	ms->aux_tab[k] = NULL;
	return (ms->aux_tab);
}

char	**parser_split(t_ms *ms, char *str)
{
	int		count;

	if (!str)
		return (NULL);
	count = parser_count(ms, str, 32);
	ms->aux_tab = malloc (sizeof(char *) * (count + 1));
	if (!ms->aux_tab)
		return (NULL);
	ms->aux_tab = parser_do_split(ms, str, 32, 0);
	if (!ms->aux_tab)
		return (NULL);
	return (ms->aux_tab);
}
