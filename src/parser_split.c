/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:59:09 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/24 21:43:56 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	parse_toggle_flag(char c, int *dq, int *sq)
{
	if (c == '\'')
	{
		if (*sq)
			*sq = 0;
		else
			*sq = 1;
	}
	else if (c == '"')
	{
		if (*dq)
			*dq = 0;
		else
			*dq = 1;
	}
}

static char	**parser_do_split(char ***tab, const char *s, char c)
{
	t_psplit	ps;

	parser_ps_init(&ps); // sq dq i k start -- todo a cero
	while (s[ps.i])
	{
		if (!(ps.dq + ps.sq))
		{
			if (s[ps.i] && s[ps.i] != c && (ps.i = 0 || s[ps.i - 1] == c))
				ps.start = ps.i;
			if (s[ps.i] && s[ps.i] == c && (s[ps.i - 1] != c))
				(*tab)[ps.k] = ft_substr(s, ps.start, ps.i - ps.start + 1);
			if (!(tab)[ps.k++])
			{
				utils_free_tab(tab);
				return (NULL);
			}
			if (s[ps.i] == '\'' || s[ps.i] == '"')
				parse_toggle_flag(s[ps.i], &ps.dq, &ps.sq);
		}
		if (s[ps.i] == '\'' || s[ps.i] == '"')
			parse_toggle_flag(s[ps.i], &ps.dq, &ps.sq);
		ps.i++;
	}
	return (*tab);
}

char	**parser_split(char *str)
{
	char	**tab;
	int		count;

	if (!str)
		return (NULL);
	count = parser_count(str, 32);
	tab = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	parser_do_split(&tab, str, 32);
	if (!tab)
		return (NULL);
	return (tab);
} 

// hola "hola hola" -> hola
// hola "esto es junto" y esto no | y esto"si que es"junto