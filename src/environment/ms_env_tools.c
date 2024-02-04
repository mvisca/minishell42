#include "../include/minishell.h"

// Adds node at the end of the list
// Tested Ok
t_envlst	*ms_addenv_node(t_minishell *ms, t_envlst *envnode)
{
	t_envlst	*aux;

	aux = ms->envlst;
	if (aux == NULL)
		ms->envlst = envnode;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = envnode;
	}
	return (ms->envlst);
}

// Creates new t_envlst node
// Tested Ok
t_envlst	*ms_newenv_node(t_minishell *ms, char *key, char *value)
{
	t_envlst	*new;

	new = (t_envlst *)malloc(sizeof(t_envlst));
	if (!new)
		ms_error_free_exit("malloc error", ms);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		ms_error_free_exit("malloc error", ms);
	}
	new->next = NULL;
	return (new);
}

// Deletes the node with the given key
// To be tested
void	ms_deleteenv(t_minishell *ms, char *key)
{
	t_envlst	*prev;
	t_envlst	*aux;

	prev = NULL;
	aux = ms->envlst;
	while (aux)
	{
		if (ft_strncmp(aux->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = aux->next;
			else
				ms->envlst = aux->next;
			free(aux->key);
			free(aux->value);
			return ;
		}
		aux = aux->next;
	}
}

// Finds the node with the key and updates its value
// To be tested
void	ms_updateenv(t_minishell *ms, char *key, char *value)
{
	t_envlst	*aux_node;

	aux_node = ms_getenv_node(ms, key);
	if (aux_node)
		aux_node->value = ft_strdup(value);
}
