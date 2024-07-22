/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:55 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/07/22 07:33:07 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expander_filter_quotes(char *str)
{
	size_t	i;
	size_t	end;
	char	quote;

	i = 0;
	if (!str)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			quote = str[i];
			end = i;
			str_close_quote(str, (size_t *)&end);
			if (str[end] == quote)
			{
				ft_memmove(&str[end], &str[end + 1], ft_strlen(&str[end]) + 1);
				ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i]) + 1);
				i = end - 2;
			}
		}
		i++;
	}
	return (str);
}

void	expander_tilde(t_ms *ms, t_coml *n, int i, char *tmp1)
{
	t_envl	*aux;
	char	*tmp2;

	if (n->command[i][0] == '~' && (n->command[i][1] == '/' || !n->command[i][1]))
	{
		aux = environment_get_node(ms, "HOME");
		if (!aux)
			tmp1 = ft_strdup("/");
		else
			tmp1 = ft_strdup(aux->value);
		if (n->command[i][1] == '/')
		{
			tmp2 = ft_strdup(&n->command[i][1]);
			free(n->command[i]);
			n->command[i] = ft_strjoin(tmp1, tmp2);
			free(tmp2);
			free(tmp1);
		}
		else
		{
			free(n->command[i]);
			n->command[i] = tmp1;
		}
	}
}
