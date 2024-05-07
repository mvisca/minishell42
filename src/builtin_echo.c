/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:36:21 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/08 01:06:34 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// -n omite nueva línea al final

static int  line_break(char *str)
{
	int	i;

	i = 0;
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

// int	main(int ac, char **av)
// {
// 	if (ac > 1 )
// 	{
// 		if (!ft_strncmp(av[1], "exit\0", 5))
// 			return (0);
// 		if (ac > 2 && !ft_strncmp(av[1], "echo\0", 5))
// 			builtin_echo(&av[1]);
// 	}
// 	return (0);
// }

// compilar con 'cc src/builtin_echo.c -L./lib/libft -lft -I./include'
