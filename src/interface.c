/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 05:07:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/03 17:21:22 by fcatala-         ###   ########.fr       */
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

static int	ft_lastispipe(char *trim)
{
	if (ft_strlen(trim) > 1)
	{
		if (trim[ft_strlen(trim) - 1] == '|')
			return (1);
	}
	return (0);
}

char	*ft_strjoinp(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s1)
	{
		while (s1[i])
			result[j++] = s1[i++];
		free(s1);
	}
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

int	interface_get_line(t_ms *ms)
{
	char	*trim;
	char	*line2;

	ms->line = readline("Minishell > ");
	trim = ft_strtrim(ms->line, SPACES);
	while (trim && trim[0] != '\0' && ft_lastispipe(trim))
	{
		line2 = readline("> ");
		free(trim);
		trim = ft_strtrim(line2, SPACES);
		ms->line = ft_strjoinp(ms->line, line2);
		free(line2);
	}
	if (!trim || trim[0] == '\0')
	{
		free(trim);
		if (!ms->line && isatty(STDIN_FILENO))
			empty_exit(ms);
		else if (ms->line)
			utils_free_ms(ms, FALSE);
		return (1);
	}
	free(trim);
	add_history(ms->line);
	return (0);
}
