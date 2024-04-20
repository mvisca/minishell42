/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:57:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/18 00:26:23 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_exit(char *msj, t_ms *ms)
{
	(void)ms;
	ft_putstr_fd(msj, 2);
	exit (1);
}

void	error_free_exit(char *msj, t_ms *ms)
{
	utils_free_ms(ms, TRUE);
	ft_printf("%s\n", msj);
	exit (1);
}
