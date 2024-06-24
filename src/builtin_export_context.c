/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_context.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/06/24 11:03:24 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export_context_error(t_ms *ms, char *key)
{					
	ft_putstr_fd("export: not valid in this context: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("+\n", 2);
	strs_free(ms);
	return (1);
}

int	export_context_expand(t_ms *ms, t_coml *cmnd, int i, int j)
{
	int	k;
	int	l;

	k = 0;
	export_ff(&k, cmnd->command[i]);
	export_get_key_value(k, cmnd->command[i], &ms->strs.aux, &ms->strs.buf);
	free(ms->strs.buf);
	l = 0;
	export_ff(&l, cmnd->command[j]);
	export_get_key_value(l, cmnd->command[j], &ms->strs.new, &ms->strs.buf);
	ft_printf("antes de la condicion %s\n", &cmnd->command[j][l]);
	if ((cmnd->command[i][k] == '+' || cmnd->command[j][l] == '+') && \
	ft_strnstr(ms->strs.aux, ms->strs.new, ft_strlen(ms->strs.aux)))
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
