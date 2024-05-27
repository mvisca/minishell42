/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/27 18:36:11 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



static int	builtin_export_declare(t_envl *env,  t_ms *ms)
{
	while (env)
	{
		ft_printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
	ms->exit_code = 0;
	return (0);
}

int	builtin_export(t_coml *cmnd, t_ms *ms)
{
	t_envl	*env;

	env = ms->envlst;
	if (cmnd->command[1] == NULL)
		builtin_export_declare(env, ms);
}


	// validar que cmnd[] no sea vacío
		// Si es vacío hace algo más



	// si hay comando
		// bucle en lista de comandos para exportar todas las variables que se definenen
/*
Caso 1
export

declare -x KEY=VALUE

Caso 2
export algo


*/
