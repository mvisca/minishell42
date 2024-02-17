/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:48:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/17 23:30:25 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	array_alloc(t_coml *comnd, t_tokl *start, t_tokl *end)
{
	int		len;
	t_tokl	*aux;
	char	**command;

	len = 0;
	aux = start;
	while (aux != end)
	{
		len++;
		aux = aux->next;
	}
	command = (char **)malloc(sizeof(char *) * (len + 1));
	if (!command)
		return (1);
	command[0] = NULL;
	comnd->command = command;
	return (0);	
}

int array_append(t_coml *comnd, t_tokl *s, t_tokl *e)
{
	int		i;

	if (!comnd->command)
		array_alloc(comnd, s, e);
	if (!comnd->command)
		return (1);
	i = ft_tablen(comnd->command);
	comnd->command[i] = ft_strdup(s->str);
	comnd->command[i + 1] = NULL;
	return (0);
}
