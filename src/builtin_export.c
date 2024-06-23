/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/23 13:19:35 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_solo(t_ms *ms, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(ft_strlen(line), line, &key, &value);
	node = environment_get_node(ms, key);
	environment_del_node(ms, key);
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
	free(key);
	free(value);
	return (1);
}

static void	export_assign(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(j, line, &key, &value);
	node = environment_get_node(ms, key);
	if (node)
		environment_del_node(ms, key);
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
	free(key);
	free(value);
}

static void	export_concat(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(j, line, &key, &value);
	node = environment_get_node(ms, key);
	if (node && node->value && (node->value)[0] != '\n')
	{
		ms->strs.aux = ft_strjoin(node->value, value);
		environment_del_node(ms, key);
		node = environment_new_node(ms, key, ms->strs.aux);
		environment_add_node(ms, node);
		free(ms->strs.aux);
		ms->strs.aux = NULL;
	}
	else
		export_assign(ms, j, line);
	free(key);
	free(value);
}

static int	export_switch(t_ms *ms, char *line, int j)
{
	strs_reset(ms);
	export_ff(&j, line);
	if (line[j] && line[j] == '+' && line[j + 1] == '=')
		export_concat(ms, j, line); // concat
	else if (line[j] == '=')
		export_assign(ms, j, line); // assign
	else if (line[j] == '\0')
		export_solo(ms, line);
	else
		export_error(line);
	return (0);
}

int	builtin_export(t_ms *ms, t_coml *cmnd)
{
	int		i;
	char	*line;

	i = 1;
	if (export_no_options(cmnd))
		return (export_print_env(ms));
	while (cmnd->command[i] != NULL)
	{
		line = cmnd->command[i];
		if (line[0] != '\n')
		{
			if (line[0] && !ft_strchr(EXP_CHARS, line[0]))
				export_error(line);
			else if (line[0])
			{
				if (i == 1 && export_context(ms, cmnd, 1, 0))
					return (1); // sujeto a comprobación en 42 si se reproduce el mensaje
				export_switch(ms, line, 0);
			}
			else
				export_error(line);
		}
		i++;
		strs_free(ms);
	}
	return (0);
}
