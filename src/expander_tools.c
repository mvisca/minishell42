/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:55 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/07/01 10:49:46 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expander_filter_quotes(t_ms *ms, char *str)
{
	size_t	i;
	size_t	end;
	char	quote;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			quote = str[i];
			end = i;
			str_close_quote(ms, str, (size_t *)&end);
			if (str[end] == quote)
			{
				ft_memmove(&str[end], &str[end + 1], ft_strlen(&str[end]));
				ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i]));
				i = end - 2;
			}
		}
		i++;
	}
	return (str);
}
