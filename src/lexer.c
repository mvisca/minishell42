/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:48:44 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/02 09:54:02 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokl	*lexer_add_token(t_ms *ms, t_tokl *token)
{
	t_tokl	*aux;

	aux = ms->token_list;
	if (!aux)
		ms->token_list = token;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = token;
	}
	return (aux);
}

int	lexer_make_token(t_ms *ms, char *line, int type, int *i)
{
	t_tokl	*new;
	size_t	len;

	new = (t_tokl *)malloc(sizeof(t_tokl));
	if (!new)
		return (1);
	new->type = type;
	new->str = NULL;
	new->next = NULL;
	if (type == WORD)
	{
		len = str_line_len(line);
		new->str = ft_substr(line, 0, len);
		if (line[*i])
			len++;
		(*i) += len -1;//el -1 es necesario para evitar salir del puntero
		ft_printf("\nvoy hasta %d\n", (int)(*i));
	}
	else
	{
		if (line)
			new->str = ft_strdup(line);
		ft_printf(BLUE "New line" RED " %s\n" RESET, new->str);
		(*i) += ft_strlen(new->str);
	}
	lexer_add_token(ms,new);
	return (0);
}

int	lexer(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	while (line && line[i] && line[i + 1])
	{
//		ft_printf("inicio bucle, line[i] %c  -- i %d\n", line[i], i);//original
		ft_printf("inicio bucle, line[%d] = %c \n", i, line[i], i);
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
		{
			lexer_make_token(ms, "|", PIPE, &i);
			ft_printf("i %d\n", i);
		}
		else if (ft_strnstr(&line[i], ">>", 2))
		{
			lexer_make_token(ms, ">>", DR_REDIRECT, &i);
			ft_printf("i %d\n", i);
		}
		else if (ft_strnstr(&line[i], "<<", 2))
		{
			lexer_make_token(ms, "<<", DL_REDIRECT, &i);
			ft_printf("i %d\n", i);
		}
		else if (line[i] == '>')
		{
			lexer_make_token(ms, ">", R_REDIRECT, &i);
			ft_printf("i %d\n", i);
		}
		else if (line[i] == '<')
		{
			lexer_make_token(ms, "<", L_REDIRECT, &i);
			ft_printf("i %d\n", i);
		}
		else
		{
			lexer_make_token(ms, &line[i], WORD, &i);
			ft_printf("i %d\n", i);
		}
	}
	lexer_make_token(ms, NULL, END, &i);
	ft_printf("i %d\n", i);
	return (0);
}


