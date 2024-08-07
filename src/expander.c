/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/22 07:31:53 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expander_clean_strs(t_ms *ms)
{
	free(ms->strs.aux);
	free(ms->strs.buf);
	ms->strs.aux = NULL;
	ms->strs.buf = NULL;
}

static void	expander_get_expansion_append(t_ms *ms, size_t *i, char *str)
{
	size_t	start;

	start = *i;
	if (ft_strchr(&str[*i], S_QUOTE))
		str_close_quote(str, i);
	ms->strs.buf = ft_substr(str, start, *i - start + 1);
	(*i)++;
}

//str_close_quote(&str[i], &i);//linea 33 original
//			expander_var_exit(ms, str, &i);//=>str cambiado por &str[i]
int	expander_get_expansion(t_ms *ms, char *str, size_t i)
{
	int		exp;

	exp = 1;
	while (str && i < ft_strlen(str) && str[i])
	{
		if (str[i] == D_QUOTE)
			exp *= -1;
		if (exp > 0 && str[i] == S_QUOTE)
			expander_get_expansion_append(ms, &i, str);
		else if (ft_strnstr(&str[i], "$?", 2) || ft_strnstr(&str[i], "${?}", 4))
			expander_var_exit(ms, &str[i], &i);
		else if (str[i] == '$' && str[i + 1] == '{')
			expander_var_curly(ms, str, &i);
		else if (str[i] == '$' && ft_isalpha(str[i + 1]))
			expander_var_alpha(ms, str, &i);
		else
			ms->strs.buf = ft_substr(str, i++, 1);
		ms->strs.aux = ms->strs.new;
		ms->strs.new = ft_strjoin(ms->strs.aux, ms->strs.buf);
		expander_clean_strs(ms);
	}
	return (0);
}

void	expander_split(char ***cm, int i, int j)
{
	int		len;
	char	**tab;
	char	**new;

	tab = ft_split((*cm)[0], ' ');
	if (ft_tablen(tab) > 1)
	{
		len = ft_tablen(*cm) + ft_tablen(tab);
		new = ft_calloc(sizeof(char *), len);
		while (tab[++i])
			new[i] = ft_strdup(tab[i]);
		i--;
		while ((*cm)[++j])
			new[i + j] = ft_strdup((*cm)[j]);
		new[i + j] = NULL;
		utils_free_tab(cm);
		*cm = new;
	}
	utils_free_tab(&tab);
}

int	expander(t_ms *ms)
{
	int			i;
	t_coml		*node;

	strs_free(ms);
	node = ms->cmnd_list;
	while (node)
	{
		i = 0;
		while (node->command && node->command[i])
		{
			expander_get_expansion(ms, node->command[i], 0);
			free(node->command[i]);
			node->command[i] = (ms->strs.new);
			if (i == 0 && !ft_strchr(ms->strs.new, D_QUOTE) && \
			!ft_strchr(ms->strs.new, S_QUOTE))
				expander_split(&node->command, -1, 0);
			expander_filter_quotes(node->command[i]);
			expander_tilde(ms, node, i, NULL);
			ms->strs.new = NULL;
			strs_free(ms);
			i++;
		}
		node = node->next;
	}
	return (0);
}
