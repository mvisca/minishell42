#include "../../include/minishell.h"

// One-liner free and null 
void	utils_free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

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

void	utils_free_ms(t_minishell *ms)
{
	free(ms->line);
	utils_free_env_list(ms->envlst);
//	utils_free_tab(ms->envarr);
	utils_free_token_list(ms->token_list);
	utils_free_comnd_list(ms->comnd_list);
}
