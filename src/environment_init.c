#include "../include/minishell.h"

// Fix information lose when env var value includes the char '='
static int	check_oversplit(t_envlst *new, char **pair)
{
	if (pair && ft_tablen(pair) > 2)
	{
		char	*aux;
		int		i;

		if (ft_tablen(pair) < 2)
			return (1);
		i = 2;
		while (pair && pair[i])
		{
			ft_printf("\x1b[1;35mValue in new =\x1b[0m %s\n", new->value);
			aux = new->value;
			new->value = ft_strjoin(aux, "=");
			free(aux);
			aux = new->value;
			new->value = ft_strjoin(aux, pair[i]);
			free(aux);
			i++;
		}
		
		ft_printf("Key =\t'%s'\n", pair[0]);
		ft_printf("Value =\t'%s'\n", pair[1]);
		ft_printf("Join del value...%s\n", new->key);
		ft_printf("Value =\n%s\n", new->value);
	}
	return (0);
}

// Tested Ok
t_envlst	*environment_init(t_minishell *ms)
{
	int			i;
	char		**pair;
	t_envlst	*new;

	i = 0;
	while (ms->envarr && ms->envarr[i])
	{
		pair = ft_split(ms->envarr[i], '=');
		if (!pair)
			error_free_exit("malloc error", ms);
		new = environment_new_node(ms, pair[0], pair[1]);
		if (!new)
			error_free_exit("malloc error", ms);
		check_oversplit(new, pair);
		environment_add_node(ms, new);
		utils_free_tab(pair);
		i++;
	}
	return (ms->envlst);
}
