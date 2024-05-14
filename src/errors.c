/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:57:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/14 20:04:18 by fcatala-         ###   ########.fr       */
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

void	ft_error_exit(char *com, char *msj, int code)
{
	ft_putstr_fd(MINI, 2);
	if (com)
		ft_putstr_fd(com, 2);
	ft_putstr_fd(msj, 2);
	exit (code);
}

