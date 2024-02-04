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
	while (tab[i])
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	free(tab);
	tab = NULL;
}

// One-liner free and null t_envlis lists (not just nodes)
void	utils_free_envlst(t_envlst *env)
{
	t_envlst	*aux;

	while (env)
	{
		aux = env->next;
		free(aux->key);
		free(aux->value);
		free(env);
		env = aux;
	}
	env = NULL;
}

// One-liner protected free and null for t_minishell struct
void	utils_free_ms(t_minishell *ms)
{
	(void)ms;
/*	if (ms->line)
		free(ms->line);
	if (ms->cwd)
		ms_free_str(&ms->cwd);
	if (ms->old_cwd)
		ms_free_str(&ms->old_cwd);
//	if (ms->envp && ms->envp[0]) // FREED BY SYSTEM AS IT IS A COPY OF ENVP ARG
//		ms_free_tab(ms->envp);
	if (ms->token)
		ms_free_tab(ms->token);
	if (ms->tokenlst)
		ms_free_tokenlst(ms->tokenlst);
//	free(ms->tokenlst);
	if (ms->envlst)
		ms_free_envlst(ms->envlst);
//	free(ms->envlst); */
}
