/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 05:07:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/27 18:34:07 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	empty_exit(t_ms *ms)
{
	write(2, "exit\n", 5);
	free(ms->line);
	ms->line = NULL;
	utils_free_ms(ms, TRUE);
	exit (1);
}

// // Muestra un prompt customizado con nombre del proyecto
// // y el directorio actual, que obtiene de enviroments
int	interface_get_line(t_ms *ms)
{
	char 	*trim;

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
