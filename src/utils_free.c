/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:44:35 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/03 13:08:00 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

// V2
// One-linier fee and null chars matrix
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
		free((*env)->key);
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
			free((*token)->str); // 2
		free(*token); // 1
		*token = NULL;
		*token = next_token;
	}
	*token = NULL;
}

// V2
//	(1 cmnd (2.1 char **command (3.a char *command[n] 3) 2.1) (2.2 redirect (3.b path 3) 2.2) 1)

//	3.a *command		## ## ## ## ## 	// 3.b path		## ## ## ## ## ##
//	2.1 **command		##############	// 2.2 redirect	#################
//	1 cmnd				#################################################
void	utils_free_cmnd_list(t_coml **cmnd)
{
	t_redl	*next_redir;
	t_coml	*next_cmnd;
	int		i;

	ft_printf(YELLOW"utils_free_cmnd_list "RESET"out\n");
	while (*cmnd)
	{
		ft_printf(YELLOW"utils_free_cmnd_list "RESET"in\n");
		next_cmnd = (*cmnd)->next;
		while ((*cmnd)->redirect)
		{
			next_redir = (*cmnd)->redirect->next;
			free((*cmnd)->redirect->path); // 3.b
			free((*cmnd)->redirect); // 2.2
			(*cmnd)->redirect = next_redir;
		}
		i = 0;
		while ((*cmnd)->command && (*cmnd)->command[i])
			free((*cmnd)->command[i++]); // 3.a
		free ((*cmnd)->command); // 2.1
		free(*cmnd); // 1
		*cmnd = next_cmnd;
	}
}

void	utils_free_cmnd_list_fake(t_ms *ms)
{
	t_coml	*next;
	t_coml	*node;
	int		i;

	node = ms->cmnd_list_fake;
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
	ms->cmnd_list_fake = NULL;
}

int	utils_free_ms(t_ms *ms, int clean_env)
{
	if (clean_env && ms->envlst)
		utils_free_env_list(&ms->envlst);
	
	if (ms->token_list)
		utils_free_token_list(&ms->token_list);
	ft_printf("pre utils_free_ms ; ms->cmnd_list\n");
	if (ms->cmnd_list)
	{
		ft_printf("in utils_free_ms ; ms->cmnd_list\n");
		utils_free_cmnd_list(&ms->cmnd_list);
	}
	if (ms->cmnd_list_fake)
	{
		ft_printf(RED"Free línea mágica %s\n"RESET, ms->cmnd_list_fake->command[0]);
		utils_free_cmnd_list_fake(ms);
	}
	return (0);
}
