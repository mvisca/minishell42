/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:57:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 05:06:42 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	ms_put_error(t_minishell *ms, t_tokenlst *token, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(token->command[1], 2);
	ft_putstr_fd("\n", 2);
	errno = 127;
	ms->status = 127;
}
*/
void	error_exit(char *msj, t_minishell *ms)
{
	(void)ms;
	ft_printf("%s\n", msj);
	exit (1);
}

void	error_free_exit(char *msj, t_minishell *ms)
{
	utils_free_ms(ms);
	ft_printf("%s\n", msj);
	exit (1);
}
