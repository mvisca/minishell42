/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:36:21 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/24 10:55:56 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	line_break(char *str)
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

int	builtin_echo(char **com)
{
	int		i;
	int		count;
	char	*str;

	i = 1;
	if (com[1] && line_break(com[1]))
		i++;
	while (com[i])
	{
		str = ft_strtrim(com[i], SPACES);
		if (str[0] > 0)
			count = ft_printf("%s", str);
		else
			count = ft_printf("%s", &str[1]);
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
