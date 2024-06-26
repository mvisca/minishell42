/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:36:21 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/26 17:55:50 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	line_break(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	if (str[i] == '-' && str[i + 1] == 'n')
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

int	builtin_echo(char **com)
{
	int		i;
	char	*str;
	int		count;

	i = 1;

	while (com[i] && line_break(com[i]))
		i++;
	while (com[i])
	{
		count = 0;
		str = ft_strtrim(com[i], SPACES);
		count = printf("%s", str);
		if (count && com[i + 1])
			printf(" ");
		free(str);
		i++;
	}
	if (!line_break(com[1]))
		printf("\n");
	return (0);
}
