#include "../include/minishell.h"

// Tested OK
t_envlst	*environment_get_node(t_minishell *ms, char *key)
{
	t_envlst	*aux_node;

	aux_node = ms->envlst;
	while (aux_node)
	{
		if (ft_strnstr(aux_node->key, key, ft_strlen(key)))
			return (aux_node);
		aux_node = aux_node->next;
	}
	return (NULL);
}

// Revisar si queremos que devuelva un string alocado o la dirección del value
// Tested Ok
char	*environment_get_value(t_minishell *ms, char *key)
{
	t_envlst	*aux_node;

	aux_node = environment_get_node(ms, key);
	if (aux_node)
		return (ft_strdup(aux_node->value));
	return (NULL);
}
