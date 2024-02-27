/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 19:31:43 by mvisca           ###   ########.fr       */
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

void	utils_free_comnd_list_fake(t_ms *ms)
{
	t_coml	*next;
	t_coml	*node;
	int		i;

	node = ms->comnd_list_fake;
	while (node)
	{
		next = node->next;
		i = 0;
		while (node->command[i])
			free(node->command[i++]);
		free(node->command);
		if (node->redirect && node->redirect->path)
			free(node->redirect->path);
		if (node->redirect)
			free(node->redirect);
		free(node);
		node = next;
	}
	ms->comnd_list_fake = NULL;
}

void	utils_free_comnd_list(t_ms *ms)
{
	t_coml	*next;
	t_coml	*node;
	int		i;

	node = ms->comnd_list;
	while (node)
	{
		next = node->next;
		i = 0;
		while (node->command && node->command[i])
			free(node->command[i++]);
		free(node->command);
		if (node->redirect && node->redirect->path)
			free(node->redirect->path);
		if (node->redirect)
			free(node->redirect);
		free(node);
		node = next;
	}
	ms->comnd_list = NULL;
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
		free(token);
		token = NULL;
		token = next;
	}
	ms->token_list = NULL;
}

int	utils_free_ms(t_ms *ms)
{
	if (ms->envlst)
		utils_free_env_list(ms->envlst);
	if (ms->token_list)
		utils_free_token_list(ms);
	if (ms->comnd_list)
		utils_free_comnd_list(ms);
	if (ms->comnd_list_fake)
	{
		ft_printf("Linea mágica %s\n", ms->comnd_list_fake->command[0]);
		utils_free_comnd_list_fake(ms);
	}
	return (0);
}
