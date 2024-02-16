/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 07:11:37 by mvisca           ###   ########.fr       */
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
void	utils_free_env_list(t_envlst *env)
{
	t_envlst	*next;

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

void	utils_free_token_list(t_tokenlst *token)
{
	t_tokenlst	*next;

	while (token)
	{
		next = token->next;
		free(token->str);
		free(token);
		token = next;
	}
	token = NULL;
}

void	utils_free_comnd_list(t_comndlst *comnd)
{
	t_comndlst	*next;

	while (comnd)
	{
		next = comnd->next;
		free(comnd->command);
		free(comnd->redirect);
		free(comnd);
		comnd = next;
	}
	comnd = NULL;
}

int	utils_free_ms(t_minishell *ms)
{
	if (ms->envlst)
		utils_free_env_list(ms->envlst);
	if (ms->envarr)
		utils_free_tab(ms->envarr);
	if (ms->token_list)
		utils_free_token_list(ms->token_list);
	if (ms->comnd_list)
		utils_free_comnd_list(ms->comnd_list);
	return (1);
}
