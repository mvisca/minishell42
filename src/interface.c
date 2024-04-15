/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 05:07:46 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/15 22:54:12 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	*split_working_dir(t_ms *ms)
// {
// 	char	*full_path;
// //	char	**split_path;
// //	char	*last_path;

// 	full_path = environment_get_value(ms, "PWD");
// //	full_path = ft_strdup(full_path);
// //	if (!full_path || full_path[0] == '\0')
// //		return (ft_strdup("\001"GREEN"/\002\001"RESET"\002"));
// //	split_path = ft_split(full_path, '/');
// //	if (!full_path || full_path[0] == '\0')
// //		return (ft_strdup("\001"GREEN"/\002"));
// //	last_path = split_path[ft_tablen(split_path) - 1];
// //	last_path = ft_strdup(last_path);
// //	free(full_path);
// //	utils_free_tab(&split_path);
// //	return (last_path);
// 	return (full_path);
// }

/*static char	*build_prompt(t_ms *ms)
{
	char	*full_path;
	char	*aux;
	char	*prompt;

	full_path = environment_get_value(ms, "PWD");
	full_path = ft_strdup(full_path);
	if (!full_path)
		return (NULL);
	aux = ft_strjoin(TITLE, full_path);
	prompt = ft_strjoin(aux, " $> \001"RESET"\002");
	free(full_path);
	free(aux);
	return (prompt);
}*/

// Muestra un prompt customizado con nombre del proyecto
// y el directorio actual, que obtiene de enviroments
int	interface_get_line(t_ms *ms)
{
//	char	*prompt;
	char 	*trim;

//	prompt = build_prompt(ms);
//	if (!prompt)
//		return (1);
//	ft_printf("pid %d\n", getpid());
	ms->line = readline("Minishell > ");
//	free(prompt);
	trim = ft_strtrim(ms->line, SPACES);
	if (!trim || trim[0] == '\0')
	{
		free(ms->line);
		free(trim);
		return (1);
	}
	free(trim);
	add_history(ms->line);
	return (0);
}
