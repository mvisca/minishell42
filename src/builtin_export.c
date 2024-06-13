/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/13 17:06:25 by mvisca           ###   ########.fr       */
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

static int	update_env(t_ms *ms, char *key, char *value)
{
	t_envl	*node;
	t_envl	*new_node;

	ft_printf("key %s - value %s\n", key, value);
	node = environment_get_node(ms, key);
	if (node)
	{
		environment_update_node(ms, key, value);
		free(key);
	}
	else
	{
		new_node = environment_new_node(ms, key, value);
		if (!new_node)
			return (1);
		environment_add_node(ms, new_node);
	}
	return(0);
}

static int	options(t_ms *ms, int j)
{
	char	*key;
	char	*value;

	if (ms->strs.aux[j] == '\0')
		return (0);
	key = ft_substr(ms->strs.aux, 0, j);
	if (ms->strs.aux[j] == '=')
		value = ft_strdup(&ms->strs.aux[j + 1]);
	else if (ms->strs.aux[j] == '+')
	{
		ms->strs.buf = environment_get_value(ms, key);
		ms->strs.new = &ms->strs.aux[j + 2];
		value = ft_strjoin(ms->strs.buf, ms->strs.new);
//		free(ms->strs.buf);
	}
	update_env(ms, key, value);
	free(key);
	free(value);
	strs_reset(ms);
	return (0);	
}

int	builtin_export(t_ms *ms, t_coml *cmnd)
{
	int		i;
	int		j;

	i = 1;
	if (no_options(cmnd))
		return (export_print_env(ms));
	while (cmnd->command[i])
	{
		j = 0;
		ms->strs.aux = cmnd->command[i++];
		if (ms->strs.aux[0] == '\n')
			ms->strs.aux[0]= '\0';
		if (!ft_strchr(EXP_CHARS, ms->strs.aux[0]))
			export_error(ms->strs.aux);
		while (ms->strs.aux[j] && ft_strchr(EXP_CHARS, ms->strs.aux[j]))
			j++;
		if (!ms->strs.aux[j] || ms->strs.aux[j] == '=' || \
			(ms->strs.aux[j] == '+' && ms->strs.aux[j + 1] == '='))
//			!ft_strncmp(&ms->strs.aux[j], "+=", 2))
			options(ms, j);
		else
			export_error(ms->strs.aux);
	}
	strs_reset(ms);
	return (0);
}