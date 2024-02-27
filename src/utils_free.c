/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 00:07:51 by mvisca           ###   ########.fr       */
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

void	utils_free_token_list(t_ms *ms)
{
	t_tokl	*next;
	t_tokl	*token;

	token = ms->token_list;
	while (token)
	{
		next = token->next;
		if (token->str)
			free(token->str);
		if (token)
			free(token);
		token = NULL;
		token = next;
	}
	ms->token_list = NULL;
}

void	utils_free_comnd_list(t_coml *comnd)
{
	t_coml	*next;
	int		i;

	while (comnd)
	{
		next = comnd->next;
		i = 0;
		while (comnd->command[i])
			free(comnd->command[i++]);
		free(comnd->command);
		if (comnd->redirect && comnd->redirect->path)
			free(comnd->redirect->path);
		if (comnd->redirect)
			free(comnd->redirect);
		free(comnd);
		comnd = next;
	}
	comnd = NULL;
}

int	utils_free_ms(t_ms *ms)
{
	if (ms->envarr)
		utils_free_tab(ms->envarr);
	if (ms->envlst)
		utils_free_env_list(ms->envlst);
	if (ms->token_list)
		utils_free_token_list(ms);
	if (ms->comnd_list)
		utils_free_comnd_list(ms->comnd_list);
	if (ms->comnd_list_fake)
	{
		ft_printf("Linea mágica %s\n", ms->comnd_list_fake->command[0]);
		utils_free_comnd_list(ms->comnd_list_fake);
	}
	return (0);
}
