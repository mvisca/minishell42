/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/03 14:28:25 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_coml	*parser_tab_to_array(char **tab, t_coml *cmnd)
{
	int		i;
	int		len_old;
	int		len_new;
	char	**new;

	i = 0;
	len_old = ft_tablen(cmnd->command);
	len_new = ft_tablen(tab);
	new = (char **)ft_calloc(len_old + len_new + 1, sizeof(char *)); 
	// new = (char **)supresedmalloc(sizeof(char *) * (len_old + len_new + 1));
	if (!new)
		return (NULL);
	while (cmnd->command && cmnd->command[i])
	{
		new[i] = cmnd->command[i];
		i++;
	}
	while (tab && tab[i - len_old])
	{
		new[i] = tab[i - len_old];
		i++;
	}
	new[i] = NULL;
	free(tab);	
	free(cmnd->command);
	cmnd->command = new;
	return (cmnd);
}

int	parser(t_ms *ms)
{
//	int		alloc_cmnd;
	t_tokl	*token;
	t_coml	*command;
	char	**tab;

//	alloc_cmnd = TRUE;
	token = ms->token_list;
	command = NULL;
	while (token->type != END)
	{
		if ( !command) // alloc_cmnd == TRUE)
		{
			parser_new_command(&command);
			if (!command)
				return (1);	
//			alloc_cmnd = FALSE;
		} // OK verified
		if (token->type == WORD)
		{
			tab = parser_split(token->str); // <<< FIX >>>
			if (!tab)
				return (1);
			parser_tab_to_array(tab, command); // OK Verified
			ft_printf(RED"Parser"RESET" -> command address "BLUE" %p\n", command->command);
			int i = 0;
			while (command->command && command->command[i])
			{
				ft_printf(RED"Parser"RESET" -> command->command[%d] = "BLUE"%s\n"RESET, i, command->command[i]);
				i++;
			}
		}
		else // caso de los redirects
		{
			ft_printf("ELSE\n");
			// extraer el redir
			// ir al siguiente nodo
				// si es word
					// split de words
						// primer elemento a redir path
						// resto del tab al array
				// si es otra cosa path == NULL 
					// ESTO DARA ERROR
		}
		token = token->next;
		// if (alloc_cmnd == TRUE) // de momento para dev (se queda?)
		// {
		// 	utils_free_cmnd_list(&ms->cmnd_list);
		// 	ms->cmnd_list = NULL;
		// }
		if (token->type == PIPE || token->type == END)
		{
			parser_add_command(ms, command); // OK
			command = NULL;
			// alloc_cmnd = TRUE;
		}
	}
//	debug_command(ms);
	return (0);
}
