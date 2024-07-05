/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:21:53 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/05 11:30:26 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_countcmd(t_coml *coml)
{
	int		i;
	t_coml	*aux;

	i = 0;
	aux = coml;
	while (aux)
	{
		aux->in = STDIN_FILENO;
		aux->out = STDOUT_FILENO;
		aux = aux->next;
		++i;
	}
	return (i);
}

char	*ft_getcmd(char *cmnd, t_ms *ms, int last)
{
	int		i;
	int		aux;
	char	*out;
	char	**paths;

	if (!cmnd[0])
		ft_error_exit(EMPTY, NO_FOUND, last * EXIT_NOTFOUND);
	out = environment_get_value(ms, "PATH");
	if (!out)
		return (ft_strjoin("/", cmnd));
	paths = ft_split(out, ':');
	i = -1;
	aux = -1;
	while (aux == -1 && paths[++i])
	{
		out = ft_strjoin3(paths[i], "/", cmnd);
		aux = access(out, F_OK);
		if (out && aux == -1)
			free(out);
	}
	ft_freechain(paths);
	if (aux == -1)
		ft_error_exit(cmnd, NO_FOUND, last * EXIT_NOTFOUND);
	return (out);
}

int	ft_isdir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	else
		closedir(dir);
	return (1);
}

void	ft_dup_close(int tubo[2], int pos, int out)
{
	if (pos == 1)
	{
		close(tubo[R_END]);
		if (out < 0)
		{
			if (dup2(tubo[W_END], STDOUT_FILENO) < 0)
				ft_error_exit(DUP_FAIL, strerror(errno), EXIT_FAILURE);
		}
		close(tubo[W_END]);
	}
	if (pos == 2)
	{
		close(tubo[W_END]);
		if (dup2(tubo[R_END], STDIN_FILENO) < 0)
			ft_error_exit(DUP_FAIL, strerror(errno), EXIT_FAILURE);
		close(tubo[R_END]);
	}
}

void	ft_reset_dups(t_ms *ms)
{
	dup2(ms->init_fd[0], STDIN_FILENO);
	close(ms->init_fd[0]);
	ms->init_fd[0] = dup(STDIN_FILENO);
	dup2(ms->init_fd[1], STDOUT_FILENO);
	close(ms->init_fd[1]);
	ms->init_fd[1] = dup(STDOUT_FILENO);
}
