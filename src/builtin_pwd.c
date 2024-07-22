/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:06:43 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/22 07:43:03 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_pwd(void)
{
	char	path[MAX_PATH];

	getcwd(path, sizeof(path));
	ft_printf("%s\n", path);
	return (0);
}
