/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:55 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/04/10 15:28:27 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expander_filter_quotes(char *str)
{
	int		i;
	int		ini;
	int		end;
	char	quote;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			quote = str[i];
			ini = i;
			end = i;
			str_close_quote(str, (size_t *)&end);
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
