/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:40:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 15:46:38 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*make_token_word(char *line)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] && line[i] != '|' && line[i] != '>' && line[i] != '<')
		i++;
	word = ft_substr(line, 0, i);
	return (word);
}
