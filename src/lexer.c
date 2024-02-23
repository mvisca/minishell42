/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:48:44 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/19 21:59:05 by mvisca           ###   ########.fr       */
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
			i += make_token(ms, &l[i], PIPE);
		else if (ft_strnstr(&l[i], ">>", 2))
			i += make_token(ms, &l[i], DR_REDIRECT);
		else if (ft_strnstr(&l[i], "<<", 2))
			i += make_token(ms, &l[i], DL_REDIRECT);
		else if (l[i] == '>')
			i += make_token(ms, &l[i], R_REDIRECT);
		else if (l[i] == '<')
			i += make_token(ms, &l[i], L_REDIRECT);
		else
			i += make_token(ms, &l[i], WORD);
	}
	if (i > (int)ft_strlen(l))
		return (lexer_clean(ms));
	make_token(ms, "", END);
	skip_empty_token(ms);
	free(ms->line);
	return (0);
}
