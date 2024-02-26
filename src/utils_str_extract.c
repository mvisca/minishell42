/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_extract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 22:42:32 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 19:39:55 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	str_ints_init(t_ints *i)
{
	i->sq = 1;
	i->dq = 1;
	i->i = 0;
	i->ini = 0;
	i->len = 0;
	i->pre_cmnd = NULL;
	i->pre_redir = NULL;
	return (0);
}

static int	str_end_quote(char *str, int i, int quote_type)
{
	while (str[i] && str[i] != quote_type)
		i++;
	if (str[i])
		i++;
	return (i);
}

static int str_add_precmnd(t_coml *cmnd, t_tokl *pre_cmnd)
{
	t_tokl	*aux;

	aux = cmnd->pre_cmnd;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = pre_cmnd;
	}
	else
		cmnd->pre_cmnd = pre_cmnd;
	return (0);
}

t_tokl	*str_ext_cmnd(t_coml **cmnd, char *str)
{
	t_ints	i;

	str_ints_init(&i);
	while (str[i.i])
	{
		while (ft_isspace(str[i.i]))
			i.i++;
		i.ini = i.i;
		if (str[i.i] && str[i.i] == D_QUOTE)
			i.i = str_end_quote(str, i.i, D_QUOTE);
		else if (str[i.i] && str[i.i] == S_QUOTE)
			i.i = str_end_quote(str, i.i, S_QUOTE);
		else if (!str[i.i] || ft_isspace(str[i.i]))
		{
			i.len = (size_t) (i.i - i.ini);
			i.pre_cmnd = (t_tokl *)malloc(sizeof(t_tokl));
			if (!i.pre_cmnd)
				return (NULL);
			i.pre_cmnd->str = ft_substr(str, i.ini, i.len);
			if (!i.pre_cmnd->str)
				return (NULL);
			str_add_precmnd(*cmnd, i.pre_cmnd);		
		}
		i.i++;		
	}
	return ((*cmnd)->pre_cmnd);
}
