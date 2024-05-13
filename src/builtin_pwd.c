/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:06:43 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/08 08:56:13 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int builtin_pwd(t_ms *ms)
{
    ft_printf("%s\n", environment_get_value(ms, "PWD"));
    return (0);
}

// int main(int ac, char **av, char **envp)
// {
//     t_ms    ms;

//     initialize(&ms, ac, av, envp);
//     builtin_pwd(&ms);
//     return (0);
// }

// cc src/builtin_pwd.c src/environment_getters.c src/environment_init.c src/environment_tools.c src/initialize.c src/errors.c src/utils_free.c -L./lib/libft -lft -L./lib/readline -lreadline -lhistory -ltermcap -L./lib/readline/libhistory.a -I./include -I./lib/readline
