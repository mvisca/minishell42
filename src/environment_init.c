#include "../include/minishell.h"

// Tested Ok
t_envlst	*environment_init(t_minishell *ms)
{
	int			i;
	char		**pair;
	t_envlst	*new;

	i = 0;
	while (ms->envp && ms->envp[i])
	{
		pair = ft_split(ms->envp[i], '=');
		if (!pair)
			error_free_exit("malloc error", ms);
		new = environment_new_node(ms, pair[0], pair[1]);
		if (!new)
			error_free_exit("malloc error", ms);
		environment_add_node(ms, new);
		utils_free_tab(pair);
		i++;
	}
	return (ms->envlst);
}
