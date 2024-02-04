#include "../../include/minishell.h"

// Generates a prompt displying curret working directory
// Refactorizar usando una función custom que saque el último valor de un tab...
// usa ft_tablen(tab) para obtener el largo y devuelve:
// tab[tablen(tab) - 1]
static char	*ms_build_prompt(t_minishell *ms)
{
	char	*aux_str1;
	char	*aux_str2;
	char	**aux_tab;
	char	*prompt;

	aux_str1 = ft_strdup("💻 \x1b[33mMiniShell \x1b[1;35m@ \x1b[0m");
	aux_str2 = ms_getenv_value(ms, "PWD");
	aux_tab = ft_split(aux_str2, '/');
	free(aux_str2);
	aux_str2 = aux_tab[ft_tablen(aux_tab) - 1];
	prompt = ft_strjoin(aux_str1, aux_str2);
	free(aux_tab); // esto estaría dejando leaks porque es un tab y nno se libera lo demás...
	free(aux_str1);
	free(aux_str2);
	aux_str1 = prompt;
	prompt = ft_strjoin(aux_str1, " > ");
	free(aux_str1);
	return (prompt);
}

// Muestra un prompt customizado con nombre del proyecto y el directorio actual, que obtiene de enviroments
void	ms_get_line(t_minishell *ms)
{
	char	*prompt;

	prompt = ms_build_prompt(ms);
	ms->line = readline(prompt);
	add_history(ms->line);
	free(prompt);
}