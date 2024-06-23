
#include "../include/minishell.h"



static int	environment_is_sort(t_ms *ms)
{
	int		sort;
	t_envl	*curr;
	t_envl	*prev;

	sort = 1;
	curr = ms->envlst->next;
	prev = ms->envlst;
	while (curr)
	{
		if (prev->key > curr->key)
		{
			sort = 1;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (sort);
}

static int	environment_swap(t_envl **prev, t_envl **curr)
{
	(*prev)->next = (*curr)->next;
	*curr = (*curr)->next;
	return (0);
}

t_envl    *environment_sort(t_ms *ms_p)
{
	// ver nodo a nodo cuál es el key mayor
	t_envl  *curr;
	t_envl	*prev;

	prev = ms_p->envlst;
	curr = ms_p->envlst->next;
	if (ft_strcmp(prev->key, curr->key) > 0)
		environment_swap(&curr, &curr->next);
	while (!environment_is_sort(ms_p))
	{
		if (ft_strcmp(prev->key, curr->key) > 0)

			environment_swap(&prev, &curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
		if (!curr)
			curr = ms_p->envlst;
	}
	return (ms_p->envlst);
}
