#include "../include/minishell.h"

static char	*split_working_dir(t_minishell *ms)
{
	char	*full_path;
	char	**split_path;
	char	*last_path;

	full_path = environment_get_value(ms, "PWD");
	// testear el retorno de enviroment get value cuando estoy en root, en base a la respuesta hacer la protección del split... ahora está redundante
	if (!full_path || full_path[0] == '\0')
		return(ft_strdup("/"));
	split_path = ft_split(full_path, '/');
	if (!full_path || full_path[0] == '\0')
		return(ft_strdup("/"));
	last_path = split_path[ft_tablen(split_path) - 1];
	last_path = ft_strdup(last_path);
	free(full_path);
	utils_free_tab(split_path);
	return (last_path);
}

static char	*build_prompt(t_minishell *ms)
{
	char	*title;
	char	*workindg_dir;
	char	*aux;
	char	*prompt;

	title = ft_strdup(TITLE);
	workindg_dir = split_working_dir(ms);
	aux = ft_strjoin(title, workindg_dir);
	prompt = ft_strjoin(aux, " > ");
	free(title);
	free(workindg_dir);
	free(aux);
	return (prompt);
}

// Muestra un prompt customizado con nombre del proyecto y el directorio actual, que obtiene de enviroments
void	interface_get_line(t_minishell *ms)
{
	char	*prompt;

	prompt = build_prompt(ms);
	ms->line = readline(prompt);
	add_history(ms->line);
	free(prompt);
}