/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:36:21 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/18 18:41:49 by fcatala-         ###   ########.fr       */
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

static int	echo_print(char **com, int i)
{
	int		count;
	int		j;
	char	*str;

	j = 0;
	count = 0;
	str = ft_strtrim(com[i], SPACES);
	while (str[j])
	{
//		if (str[j] < 0 && str[j + 1] != 0)
//			count = printf("\n");//<== xq se hace esto?
//		if (str[j] > 0)
			count = printf("%c", str[j]);
		j++;
	}
	free(str);
	return (count);
}

int	builtin_echo(char **com)
{
	int		i;
	int		count;

	i = 1;
	while (com[i] && line_break(com[i]))
		i++;
	i--;
	while (com[++i])
	{
		if (com[i][0] < 0 && com[i][1] == 0)
			continue ;
		count = echo_print(com, i);
		if (count && com[i + 1])
			printf(" ");
	}
	if (!line_break(com[1]))
		printf("\n");
	return (0);
}
