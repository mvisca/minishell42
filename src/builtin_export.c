/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/05 20:24:41 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_switch(t_ms *ms, char *line, int j)
{
	strs_reset(ms);
	export_ff(&j, line);
	if (line[j] && line[j] == '+' && line[j + 1] == '=')
		export_concat(ms, j, line);
	else if (line[j] == '=')
		export_assign(ms, j, line);
	else if (line[j] == '\0')
		export_solo(ms, line);
	else
		export_error(line);
	return (0);
}

static int	export_not_new_line(t_ms *ms, t_coml *cmnd, char *line, int i)
{
	if (line[0] && !ft_strchr(EXP_CHARS, line[0]))
		export_error(line);
	else if (line[0])
	{
		if (i == 1 && export_context(ms, cmnd, 1, 0))
			return (1);
		export_switch(ms, line, 0);
	}
	else
		export_error(line);
	return (0);
}

int	builtin_export(t_ms *ms, t_coml *cmnd)
{
	int		i;
	char	*line;

	i = 0;
	if (export_no_options(cmnd))
		return (export_print_env(ms));
	while (cmnd->command[++i] != NULL)
	{
		line = cmnd->command[i];
		if (line[0] != '\n')
			export_not_new_line(ms, cmnd, line, i);
		else
		{
			ft_memmove(cmnd->command[i], &cmnd->command[i][1], \
			ft_strlen(&cmnd->command[i][1]));
			export_error(cmnd->command[i]);
		}
		strs_free(ms);
	}
	return (0);
}
