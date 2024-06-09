/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:36:21 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/09 15:34:28 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// -n omite nueva línea al final
// corregido el error cuando se pasaba echo sin argumentos :-)
static int  line_break(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
		{
			i++;
			if (!str[i])
				return (TRUE);
		}	
	}	
	return (FALSE);
}

int builtin_echo(char **com)
{
	int i;

	i = 1;
	if (com[1] && line_break(com[1]))
		i++;
	while (com[i])
	{
		if (com[i][0] != '\n')
			ft_printf("%s", com[i]);
		i++;
		if (!com[i])
			break ;
		else
			ft_printf(" ");
	}
	if (!line_break(com[1]))
		ft_printf("\n");
	return (0);
}
