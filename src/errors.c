/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:57:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/29 12:35:54 by fcatala-         ###   ########.fr       */
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
	if (ft_strcmp(EMPTY, com))
		ft_free_nullify(&com);
	ft_putstr_fd(msj, 2);
	exit (code);
}

void	ft_error_noexit(char *com, char *path, char *msj)
{
	ft_putstr_fd(MINI, 2);
	if (com)
		ft_putstr_fd(com, 2);
	if (path)
	{
		ft_putstr_fd(path, 2);
		free(path);
	}
	ft_putstr_fd(msj, 2);
}

int	ft_error_return(char *com, char *path, char *msj, int code)
{
	ft_putstr_fd(MINI, 2);
	if (com)
		ft_putstr_fd(com, 2);
	if (path)
		ft_putstr_fd(path, 2);
	if (msj)
		ft_putstr_fd(msj, 2);
	return (code);
}
