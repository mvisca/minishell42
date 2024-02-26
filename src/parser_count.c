/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:13:12 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/25 23:25:54 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_count_words(char *str)
{
	int	i;
	int	dq;
	int	sq;
	int	len;

	i = 0;
	dq = 1;
	sq = 1;
	len = 0;
	while (str[i])
	{
		while (str[i] &&dq > 0 && sq > 0 && ft_isspace(str[i]))
			i++;
		if (dq > 0 && str[i] == S_QUOTE)
			sq *= -1;
		else if (sq > 0 && str[i] == D_QUOTE)
			dq *= -1;
		else if ((sq < 0 || dq < 0))
		{
			len++;
			while (str[i] && ((sq < 0 && str[i] != S_QUOTE) \
			|| (dq < 0 && str[i] != D_QUOTE)))
				i++;
			continue ;
		}
		else if (sq > 0 && dq > 0)
		{
			len++;
			while(str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE \
			&& !ft_isspace(str[i]))
				i++;
			continue ;
		}
		i++;
	}
	ft_printf(SEAGREEN"end parser count words %d\n", len);
	return (len);
}

int	parser_count_commands(t_tokl *token)
{
	int	len;

	len = 0;
	while (token->type != PIPE && token->type != END)
	{
		if (token->type == WORD)
			len += parser_count_words(token->str);
		else
			token = token->next;
		if (token->next)
			token = token->next;
	}
	return (len);
}
