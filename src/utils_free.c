/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/17 20:57:08 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// One-linier fee and null chars matrix
void	free_tab(char **tab)
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
void	free_env_list(t_envl *env)
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

void	free_token_list(t_tokl *token)
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

static void	free_redir(t_redl *redir)
{
	t_redl	*aux;
	
	while (redir)
	{
		aux = redir;
		free(aux->path);
		free(redir);
		redir = aux->next;
	}
}

void	free_comnd_list(t_coml *comnd)
{
	t_coml	*next;

	while (comnd)
	{
		next = comnd->next;
		free_redir(comnd->redirect);
		free(comnd->redirect);
		free(comnd->command);
		comnd->command = NULL;
		comnd->redirect = NULL;
		free(comnd);
		comnd = next;
	}
	comnd = NULL;
}

int	free_ms(t_ms *ms)
{
	if (ms->envlst)
		free_env_list(ms->envlst);
	if (ms->envarr)
		free_tab(ms->envarr);
	if (ms->token_list)
		free_token_list(ms->token_list);
	if (ms->comnd_list)
		free_comnd_list(ms->comnd_list);
	return (1);
}
