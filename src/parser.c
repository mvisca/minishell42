/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/28 09:44:14 by mvisca           ###   ########.fr       */
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
	new = (char **)malloc(sizeof(char *) * (len_old + len_new + 1));
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
	free(cmnd->command);
	cmnd->command = new;
	return (cmnd);
}

int	parser(t_ms *ms)
{
	int		cmnd_new;
	t_tokl	*start;
	t_coml	*command;
	char	**tab;

	cmnd_new = TRUE;
	start = ms->token_list;
	command = NULL;
	while (start->type != END)
	{
		if (cmnd_new == TRUE)
		{
			command = parser_new_command(command);
			if (!command)
				return (1);	
			cmnd_new = FALSE;
		} // OK verified
		if (start->type == WORD)
		{
			tab = parser_split(start->str); // <<< FIX >>>
			if (!tab)
				return (1);
			parser_tab_to_array(tab, command); // OK Verified	
			ft_printf(RED"Parser"RESET" -> command addres "BLUE" %p\n", command->command);
			int i = -1;
			while (command->command && command->command[++i])
				ft_printf(RED"Parser"RESET" -> command->command[%d] = "BLUE"%s\n", i, command->command[i]);
			parser_add_command(ms, command); // OK
		}
		else if (start->type == PIPE)
			cmnd_new = TRUE;
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
		start = start->next;
		if (cmnd_new == TRUE) // de momento para dev (se queda?)
		{
			utils_free_comnd_list(ms);
			ms->comnd_list = NULL;
		}	
	}
//	debug_command(ms);
	return (0);
}
