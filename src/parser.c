/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/04 22:36:12 by mvisca           ###   ########.fr       */
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

static int	parser_is_redir(t_coml **cmnd, t_tokl **token, t_redl **redir, char ***tab)
{
	*redir = (t_redl *)ft_calloc(1, sizeof(t_redl));
	if (!*redir)
		return (1);

	(*redir)->type = (*token)->type;
	(*redir)->path = NULL;
	(*redir)->next = NULL;
	*token = (*token)->next;
	if (!*token)
		return (1);
	if ((*token)->type == WORD)
	{
		*tab = parser_split((*token)->str);
		if (!*tab)
			return (1);
		(*redir)->path = (*tab)[0];
		if ((*tab)[1])
			parser_tab_to_array(&(*tab)[1], *cmnd);
		free(*tab);
	}
	parser_add_redirect(*cmnd, *redir);
	return (0);
}

static int	parser_populate_command(t_ms **ms, t_coml **cmnd, t_tokl **token, t_redl **redir)
{
	char **tab;

	if ((*token)->type == WORD)
	{
		tab = parser_split((*token)->str);
		if (!tab)
			return (1);
		parser_tab_to_array(tab, *cmnd);
		free(tab);
	}
	else if ((*token)->type >= 5 && (*token)->type <= 8)
	{
		if (parser_is_redir(cmnd, token, redir, &tab))
			return (1);
	}
	if ((*token)->next)
		*token = (*token)->next;
	if ((*token)->type == PIPE || (*token)->type == END)
	{
		parser_add_command(*ms, *cmnd); 
		*cmnd = NULL;
	}
	return (0);
}

int	parser(t_ms *ms)
{
	t_tokl	*token;
	t_coml	*cmnd;
	t_redl	*redir;

	token = ms->token_list;
	cmnd = NULL;
	while (token->type != END)
	{
		if ( !cmnd)
		{
			parser_new_command(&cmnd);
			if (!cmnd)
				return (1);
		}
		if (parser_populate_command(&ms, &cmnd, &token, &redir))
			return (1);
	}
	if (parser_update_envarr(ms) != 0)
		return (1);
	return (0);
}
