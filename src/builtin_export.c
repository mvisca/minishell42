/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/29 01:48:59 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	builtin_export_no_options(t_envl *env, t_ms *ms)
{
	while (env)
	{
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	ms->exit_code = 0;
	return (0);
}

static int	builtin_export_check_options(t_coml *cmnd, t_ms *ms)
{
	int	fail;
	int	i;

	ms->exit_code = 0;
	fail = 0;
	i = 0;
	while ((ft_isalnum(cmnd->command[i])) || cmnd->command[i] == '_')
		i++;
	if ((!ft_strchr("qwertyuiopaasdfghjklñzxcvbnm", cmnd->command[0])) \
	|| (!ft_strchr("_QWERTYUIOPASDFGHJKLÑZXCVBNM", cmnd->command[0])))
		fail = 1;
	if (fail || cmnd->command[i] != '=' && cmnd->command[i] != '\0')
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(cmnd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ms->exit_code = 1;
	}
	else
	{
		// create, update, contact
	}
	return (ms->exit_code);
	// ir hasta el final recorriendo el string para ver donde esta el = y ver si el =+ va antes del =
	// hacer el concat o reemplaza
}

int	builtin_export(t_coml *cmnd, t_ms *ms)
{
	int		i;
	t_envl	*env;

	i = 1;
	env = ms->envlst;
	if (cmnd->command[1] == NULL)
	{
		builtin_export_no_options(env, ms);
		return (0);
	}
	i = 1;
	while (cmnd->command[i], ms)
	{
		builtin_export_check_options(cmnd->command[i], ms);
		i++;
	}

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
