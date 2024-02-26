/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:48:44 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 19:38:44 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lexer(t_ms *ms, char *l)
{
	int		i;

	i = 0;
	while (l && i <= (int)ft_strlen(l) && l[i])
	{
		if (l[i] == '|')
			i += lexer_make_token(ms, &l[i], PIPE);
		else if (ft_strnstr(&l[i], ">>", 2))
			i += lexer_make_token(ms, &l[i], DR_REDIRECT);
		else if (ft_strnstr(&l[i], "<<", 2))
			i += lexer_make_token(ms, &l[i], DL_REDIRECT);
		else if (l[i] == '>')
			i += lexer_make_token(ms, &l[i], R_REDIRECT);
		else if (l[i] == '<')
			i += lexer_make_token(ms, &l[i], L_REDIRECT);
		else
			i += lexer_make_token(ms, &l[i], WORD);
	}
	if (i > (int)ft_strlen(l) || lexer_end_token(ms))
		return (1);
	lexer_skip_empty_token(ms);
	free(ms->line);
	return (0);
}
