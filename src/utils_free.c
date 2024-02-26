/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 16:26:43 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

// One-linier fee and null chars matrix
void	utils_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

// One-liner free and null t_envlis lists (not just nodes)
void	utils_free_env_list(t_envl *env)
{
	t_envl	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
	env = NULL;
}

void	utils_free_token_list(t_tokl *token)
{
	t_tokl	*next;

	while (token)
	{
		next = token->next;
		free(token->str);
		token->str = NULL;
		free(token);
		token = NULL;
		token = next;
	}
	token = NULL;
}

void	utils_free_comnd_list(t_coml *cmnd)
{
	t_coml	*next;
	t_redl	*redir;
	int		i;

	while (cmnd)
	{
		next = cmnd->next;
		i = 0;
		while (cmnd->command[i])
			free(cmnd->command[i++]);
		free(cmnd->command);
		while (cmnd->redirect)
		{
			redir = cmnd->redirect->next;
			if (cmnd->redirect->path)
				free(cmnd->redirect->path);
			free(cmnd->redirect);
			cmnd->redirect = redir;
		}
		if (cmnd->pre_cmnd)
			utils_free_token_list(cmnd->pre_cmnd);
		if (cmnd->pre_cmnd)
			utils_free_token_list(cmnd->pre_redir);
		free(cmnd);
		cmnd = next;
	}
	cmnd = NULL;
}

int	utils_free_ms(t_ms *ms)
{
	if (ms->envarr)
		utils_free_tab(ms->envarr);
	if (ms->envlst)
		utils_free_env_list(ms->envlst);
	if (ms->token_list)
		utils_free_token_list(ms->token_list);
	if (ms->cmnd_list)
		utils_free_comnd_list(ms->cmnd_list);
	if (ms->comnd_list_fake)
		utils_free_comnd_list(ms->comnd_list_fake);
	return (0);
}
