#include "../include/minishell.h"

// Tested Ok
t_envlst	*ms_env_init(t_minishell *ms)
{
	int			i;
	char		**pair;
	t_envlst	*new;

	i = 0;
	while (ms->envp && ms->envp[i])
	{
		pair = ft_split(ms->envp[i], '=');
		if (!pair)
			ms_error_free_exit("malloc error", ms);
		new = ms_newenv_node(ms, pair[0], pair[1]);
		if (!new)
			ms_error_free_exit("malloc error", ms);
		ms_addenv_node(ms, new);
		ms_free_tab(pair);
		i++;
	}
	return (ms->envlst);
}
