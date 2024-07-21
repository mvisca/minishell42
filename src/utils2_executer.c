/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_executer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:43:58 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/21 10:16:54 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_builtin(t_coml *aux)
{
	if (!aux->command || !aux->command[0])
		return (0);
	if (ft_strcmp(aux->command[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(aux->command[0], "echo") == 0)
		return (2);
	else if (ft_strcmp(aux->command[0], "env") == 0)
		return (3);
	else if (ft_strcmp(aux->command[0], "export") == 0)
		return (4);
	else if (ft_strcmp(aux->command[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(aux->command[0], "cd") == 0)
		return (6);
	else if (ft_strcmp(aux->command[0], "exit") == 0)
		return (7);
	else
		return (0);
}

int	builtin_env(t_ms *ms)
{
	t_envl	*aux;

	aux = ms->envlst;
	while (aux)
	{
		printf("%s=", aux->key);
		if (aux->value && aux->value[0] > 0)
			printf("%s\n", aux->value);
		else if (aux->value && aux->value[0] <= 0)
			printf("\n");
		aux = aux->next;
	}
	return (0);
}

int	ft_execute_built(t_coml *aux, t_ms *ms, int type)
{
	if (type == 1)
		return (builtin_pwd(ms));
	else if (type == 2)
		return (builtin_echo(aux->command));
	else if (type == 3)
		return (builtin_env(ms));
	else if (type == 4)
		return (builtin_export(ms, aux));
	else if (type == 5)
		return (builtin_unset(ms, aux));
	else if (type == 6)
		return (builtin_cd(ms, aux->command, -1));
	else if (type == 7)
		return (builtin_exit(ms, aux->command));
	else
		return (0);
}

void	ft_waitend(pid_t pid, t_ms *ms)
{
	int	stat;

	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
	{
		ms->exit_code = WEXITSTATUS(stat);
	}
	else if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == SIGINT)
			ms->exit_code = 130;
		if (WTERMSIG(stat) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			ms->exit_code = 131;
			exit(131);
		}
	}
}

void	ft_wait(int count, pid_t pid[MAX_ARGS])
{
	int		stat;

	while (--count > 0)
	{
		waitpid(pid[count], &stat, 0);
	}
}
