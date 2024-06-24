#include "../include/minishell.h"

int	export_solo(t_ms *ms, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(ft_strlen(line), line, &key, &value);
	node = environment_get_node(ms, key);
	environment_del_node(ms, key);
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
	free(key);
	free(value);
	return (1);
}

void	export_assign(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(j, line, &key, &value);
	node = environment_get_node(ms, key);
	if (node)
		environment_del_node(ms, key);
	node = environment_new_node(ms, key, value);
	environment_add_node(ms, node);
	free(key);
	free(value);
}

void	export_concat(t_ms *ms, int j, char *line)
{
	char	*key;
	char	*value;
	t_envl	*node;

	export_get_key_value(j, line, &key, &value);
	node = environment_get_node(ms, key);
	if (node && node->value && (node->value)[0] != '\n')
	{
		ms->strs.aux = ft_strjoin(node->value, value);
		environment_del_node(ms, key);
		node = environment_new_node(ms, key, ms->strs.aux);
		environment_add_node(ms, node);
		free(ms->strs.aux);
		ms->strs.aux = NULL;
	}
	else
		export_assign(ms, j, line);
	free(key);
	free(value);
}