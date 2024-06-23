#include "../include/minishell.h"

// extracts var name and gets value when between curly brakets
// NO HAY QUE MANEJAR PARÉNTESIS NO CERRADO
int	expander_var_curly(t_ms *ms, char *str, size_t *i)
{
	size_t	start;

	if (!ft_strchr(&str[*i], '}'))
	{
		ft_printf("Error de paréntesis no cerrado\n");
		return (1);
	}
	*i += 2;
	start = *i;
	while (str[*i] && (str[*i] != '}'))
	{
		if (!(ft_isalnum(str[*i]) || str[*i] == '_'))
		{
			ft_printf(GREEN"Error Bad substitution 1\n"RESET);
			return (1);
		}
		(*i)++;
	}
	ms->strs.aux = ft_substr(str, start, (&str[*i] - &str[start]));
	*i += 1;
	if (!ms->strs.aux || ft_strlen(ms->strs.aux) == 0)
	{
		ft_printf("Error Bad substitution 2\n");
		return (1);
	}
	ms->strs.buf = environment_get_value(ms, ms->strs.aux);
	free(ms->strs.aux);
	ms->strs.aux = NULL;
	if (!ms->strs.buf)
		ms->strs.buf = ft_strdup("\n");
	else
		ms->strs.buf = ft_strdup(ms->strs.buf);
	return (0);
}

// extracts var name and gets value when not between curly brakets
int	expander_var_alpha(t_ms *ms, char *str, size_t *i)
{
	unsigned int	start;

	*i += 1;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	ms->strs.aux = ft_substr(str, start, (&str[*i] - &str[start]));
	ms->strs.buf = environment_get_value(ms, ms->strs.aux);
	free(ms->strs.aux);
	ms->strs.aux = NULL;
	if (!ms->strs.buf)
		ms->strs.buf = ft_strdup("\n");
	else
		ms->strs.buf = ft_strdup(ms->strs.buf);
	return (0);
}

// retrives exit code
int	expander_var_exit(t_ms *ms, char *str, size_t *i)
{
	if (ft_strnstr(str, "$?", 2))
		*i += 2;
	else if (ft_strnstr(str, "${?}", 4))
		*i += 4;
	ms->strs.buf = ft_itoa(ms->exit_code);
	return (0);
}