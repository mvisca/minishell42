/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/15 14:58:54 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	no_options(t_coml *cmnd)
{
	if (!cmnd->command[1])
		return (1);
	else if (ft_tablen(cmnd->command) == 2 && cmnd->command[1][0] == '\n')
		return (1);
	return (0);
}

static void	export_concat(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	ft_printf("concat\n");
	export_get_key_value(j, line, &key, &value);
	if (!key || key[0] == '\0')
		return ;
	if (environment_get_node(ms, key))
	{
		ms->strs.aux = environment_get_value(ms, key);
		ms->strs.new = ft_strjoin(ms->strs.aux, value);
		free(value);
		value = ms->strs.new;
		environment_del_node(ms, key);
	}
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
	free(key);
}

static void	export_assign(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	ft_printf("assign\n");
	export_get_key_value(j, line, &key, &value);
	if (!key || key[0] == '\0')
		return ;
	if (environment_get_node(ms, key))
		environment_del_node(ms, key);
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
	free(key);
	free(value);
}

int	builtin_export(t_ms *ms, t_coml *cmnd)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (no_options(cmnd))
		return (export_print_env(ms));
	while (export_set(&j, &line, cmnd->command[++i]) && line)
	{
		if (line[j] != '\n')
		{
			if (line[j])
			{
			if (!ft_strchr(EXP_CHARS, line[j]))
				export_error(line);
			export_ff(&j, line);
			if (line[j] && line[j] == '+' && line[j + 1] == '=')
				export_concat(ms, j, line); // concat
			else if (line[j] == '=')
				export_assign(ms, j, line); // assign
			}
		}
	}
	return (0);
}
