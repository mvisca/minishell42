
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
	t_ms	*ms_p;
	t_envl	*curr;

	ms_p = ft_calloc(sizeof(t_ms), 1);
	initialize(ms_p, 1, ms->envarr, ms->envarr);
	environment_sort(&(ms_p)->envlst);
	curr = ms_p->envlst;
	while (curr)
	{
		ft_printf("declare -x %s", curr->key);
		if (curr->value[0] != '\n')
		{
			if (curr->value[0] > 0)
				ft_printf("=\"%s\"", curr->value);
			else
				ft_printf("=\"\"");
		}
		ft_printf("\n");
		curr = curr->next;
	}
	utils_free_ms(ms_p, TRUE);
	free(ms_p);
	ms->exit_code = 0;
	return (0);
}
