/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:36:21 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/11 10:17:55 by mvisca           ###   ########.fr       */
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
	int 	i;
	int		count;
	char	*str;

	i = 1;
	if (com[1] && line_break(com[1]))
		i++;
	while (com[i])
	{
		str = ft_strtrim(com[i], SPACES);
		if (str[0] != '\n')
			count = ft_printf("%s", str);
		free(str);
		if (!com[i + 1])
			break ;
		else if (count && com[i + 1][0] != '\0')
			ft_printf(" ");
		i++;
	}
	if (!line_break(com[1]))
		ft_printf("\n");
	return (0);
}
