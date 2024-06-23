
#include "../include/minishell.h"

void	environment_sort(t_envl **env)
{
	// ver nodo a nodo cuál es el key mayor
	t_envl  *curr;
	t_envl	*prev;
	char	*key;
	char	*value;

	prev = *env;
	while (prev)
	{
		curr = prev->next;
		while (curr)
		{
			if (ft_strcmp(prev->key, curr->key) > 0)
			{
				key = prev->key;
				value = prev->value;
				prev->key = curr->key;
				prev->value = curr->value;
				curr->key = key;
				curr->value = value;
			}
			curr = curr->next;
		}
		prev = prev->next;
	}
}
