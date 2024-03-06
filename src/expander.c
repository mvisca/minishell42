/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:39:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/06 14:20:22 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
expandir
${variable}
$variable
${variable:-valor_por_defecto}
${variable:+valor_por_defecto}

~:dir del usuario /home
$*:todos los parámetros
$2:segundo parámetro
$0:nombre del script
$?:código de salida
$/:número de parámetros
$!:pid del último trabajo en segundo plano

$((expresión))
$[expresión]
+ - / * % , < <= > >= == != , && || !
:precedencia de operadores, paréntesis para alterar la precedencia
:variables dentro de la expresión
:funciones matemáticas dentro de la expresión

${variables/espresión/reemplazo}
*:cualquier string
?:cualquier char
*/

/*
export v1=hola
v1
v1: command not found
$(v1)
v1:command not found

*/