/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 05:07:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/24 10:54:39 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//No deberia salir como un error si se ha introducido ctr d para salir
int	empty_exit(t_ms *ms)
{
	write(2, "exit\n", 5);
	free(ms->line);
	ms->line = NULL;
	utils_free_ms(ms, TRUE);
	exit (0);
}

int	interface_get_line(t_ms *ms)
{
	char	*trim;

	ms->line = readline("Minishell > ");
	trim = ft_strtrim(ms->line, SPACES);
	if (!trim || trim[0] == '\0')
	{
		free(trim);
		if (!ms->line && isatty(STDIN_FILENO))
			empty_exit(ms);
		else if (ms->line && ms->line[0] == 0)
			utils_free_ms(ms, FALSE);
		return (1);
	}
	free(trim);
	add_history(ms->line);
	return (0);
}
