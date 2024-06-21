/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/21 10:14:36 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	export_solo(t_ms *ms, char *line)
{
	(void)ms;
	(void)line;
	return (1);
}

static void	export_concat(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(j, line, &key, &value);
	if (!key || key[0] == '\0')
		return ;
	if (environment_get_node(ms, key))
	{
		ms->strs.aux = environment_get_value(ms, key);
		ms->strs.new = ft_strjoin(ms->strs.aux, value);
		ms->strs.aux = NULL;
		value = ms->strs.new;
		environment_del_node(ms, key);
		node = environment_new_node(ms, key, value);
		environment_add_node(ms, node);
		free(key);
	}
	else
	{
		node = environment_new_node(ms, key, value);
		environment_add_node(ms, node);
		free(key);
		free(value);
	}
}

static void	export_assign(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(j, line, &key, &value);
	ft_printf("key %s value %s\n", key, value);
	if (!key || key[0] == '\0')
		return ;
	environment_del_node(ms, key);
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
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
	int		j;
	char	*line;

	i = 0;
	if (export_no_options(cmnd))
		return (export_print_env(ms));
	while (export_set(&j, &line, cmnd->command[++i]) && line)
	{
		if (line[j] != '\n')
		{
			if (line[j] && !ft_strchr(EXP_CHARS, line[j]))
				export_error(line);
			else if (line[j])
				export_switch(ms, line, j);
			else
				export_error(line);
		}
	}
	return (0);
}
