
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:30:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/19 16:01:50 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export_no_options(t_coml *cmnd)
{
	if (!cmnd->command[1])
		return (1);
	else if (ft_tablen(cmnd->command) == 2 && cmnd->command[1][0] == '\n')
		return (1);
	return (0);
}

void	export_get_key_value(int j, char *line, char **key, char **value)
{
	*key = ft_substr(line, 0, j);
	if (line && line[j])
	{
		if (line[j]	== '+')
			j += 2;
		else if (line[j] == '=')
			j += 1;
		*value = ft_substr(line, j, ft_strlen(&line[j]));
	}
	else
		*value = ft_strdup("\n\0");
}

void	export_ff(int *j, char *line)
{
	while (line && line[*j] && ft_strchr(EXP_CHARS, line[*j]))
		(*j)++;
}

int	export_error(char *command)
{
	ft_putstr_fd("Minishell: export: `", 2);
	if (command[0] > 0)
		ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	export_print_env(t_ms *ms)
{
	t_envl	*env;

	env = ms->envlst;
	// sort env
	while (env)
	{
		ft_printf("declare -x %s", env->key);
		if (env->value[0] != '\n')
		{
			if (env->value[0] > 0)
				ft_printf("=\"%s\"", env->value);
			else
				ft_printf("=\"\"");
		}
		ft_printf("\n");
		env = env->next;
	}
	ms->exit_code = 0;
	return (0);
}

int	export_context_error(t_ms *ms, char *key)
{					
	ft_putstr_fd("export: not valid in this context: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("+\n", 2);
	strs_free(ms);
	return (1);
}

// ms->strs.aux
// ms->strs.buf
// ms->strs.new
int	export_context_expand(t_ms *ms, t_coml *cmnd, int i, int j)
{
	int k;
	int	l;

	k = 0;
	export_ff(&k, cmnd->command[i]);
	export_get_key_value(k, cmnd->command[i], &ms->strs.aux, &ms->strs.buf);
	free(ms->strs.buf);
	l = 0;
	export_ff(&l, cmnd->command[j]);
	export_get_key_value(l, cmnd->command[j], &ms->strs.new, &ms->strs.buf);
	if ((cmnd->command[i][k] == '+' || cmnd->command[j][l] == '+') && \
	!ft_strnstr(ms->strs.aux, ms->strs.new, ft_strlen(ms->strs.aux)))
	{
		export_context_error(ms, ms->strs.aux);
		strs_free(ms);
		return (1);
	}
	strs_free(ms);
	return (0);
}

int	export_context(t_ms *ms, t_coml *cmnd, int i, int j)
{
	while (cmnd && cmnd->command[i])
	{
		j = i + 1;
		while (cmnd && cmnd->command[j])
		{
			if (export_context_expand(ms, cmnd, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// int	export_set(int *i, int *j, char **line, t_coml *cmnd)
// {
// 	*i = 1;
// 	*j = 0;
// 	*line = cmnd->command[1];
// 	return (1);
// }
