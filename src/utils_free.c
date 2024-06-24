/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/24 10:44:05 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	utils_free_tab(char ***tab)
{
	int	i;

	i = 0;
	while (*tab && (*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free((*tab));
	*tab = NULL;
}

// V2
// One-liner free and null t_envlis lists (not just nodes)
void	utils_free_env_list(t_envl **env)
{
	t_envl	*next;

	while (*env)
	{
		next = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = next;
	}
	*env = NULL;
}

// V2
//	2	*str	 ##
//	1	token	####
void	utils_free_token_list(t_tokl **token)
{
	t_tokl	*next_token;

	while (*token)
	{
		next_token = (*token)->next;
		if ((*token)->str)
			free((*token)->str);
		free(*token);
		*token = NULL;
		*token = next_token;
	}
	*token = NULL;
}

void	utils_free_cmnd_list(t_coml **cmnd)
{
	t_redl	*next_redir;
	t_coml	*next_cmnd;
	int		i;

	while (*cmnd)
	{
		next_cmnd = (*cmnd)->next;
		while ((*cmnd)->redirect)
		{
			next_redir = (*cmnd)->redirect->next;
			if ((*cmnd)->redirect->eof)
				free((*cmnd)->redirect->eof);
			if ((*cmnd)->redirect->path)
				free((*cmnd)->redirect->path);
			free((*cmnd)->redirect);
			(*cmnd)->redirect = next_redir;
		}
		i = 0;
		while ((*cmnd)->command && (*cmnd)->command[i])
			free((*cmnd)->command[i++]);
		free ((*cmnd)->command);
		free(*cmnd);
		*cmnd = next_cmnd;
	}
}

int	utils_free_ms(t_ms *ms, int clean_env)
{
	if (ms->line)
	{
		free(ms->line);
		ms->line = NULL;
	}
	if (clean_env && ms->envlst)
	{
		utils_free_env_list(&ms->envlst);
		ms->envlst = NULL;
	}
	if (ms->envarr)
		utils_free_tab(&ms->envarr);
	if (ms->token_list)
	{
		utils_free_token_list(&ms->token_list);
		ms->token_list = NULL;
	}
	if (ms->cmnd_list)
	{
		utils_free_cmnd_list(&ms->cmnd_list);
		ms->cmnd_list = NULL;
	}
	return (1);
}
