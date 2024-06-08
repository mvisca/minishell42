/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:52:47 by fcatala-          #+#    #+#             */
/*   Updated: 2024/06/08 21:03:00 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_unset(t_ms *ms, t_coml *cmnd)
{
	int	i;

	i = 1;
	while (cmnd->command[i])
	{
		environment_del_node(ms, cmnd->command[i]);
		i++;
	}
	ms->exit_code = 0;
	return (0);
}
