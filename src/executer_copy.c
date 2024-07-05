/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/05 17:27:52 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_runcmnd(t_coml *job, t_ms *ms, int last)
{
	t_coml	*aux;
	int		i;

	aux = job;
	i = 0;
	i = ft_is_builtin(aux);
	if (i)
		exit (ft_execute_built(aux, ms, i) * last);
	else if (!ft_strchr(aux->command[0], '/'))
		aux->command[0] = ft_getcmd(aux->command[0], ms, last);
	else if (ft_isdir(aux->command[0]))
		ft_error_exit(aux->command[0], IS_DIR, last * EXIT_DENIED);
	else if (access(aux->command[0], F_OK) != 0)
		ft_error_exit(aux->command[0], NO_FILE, last * EXIT_NOTFOUND);
	else if (access(aux->command[0], X_OK) != 0)
		ft_error_exit(aux->command[0], NO_EXEC, last * EXIT_DENIED);
	exit(last * execve(aux->command[0], aux->command, ms->envarr));
}

static void	ft_runchild(t_coml *job, t_ms *ms, int i, pid_t pid[MAX_ARGS])
{
	int		tubo[2];

	if (pipe(tubo) < 0)
		ft_error_exit("Pipe failed", NO_PIPE, EXIT_FAILURE);
	pid[i] = fork();
	if (pid[i] < 0)
		ft_error_exit("Fork failed:", NO_FORK, EXIT_FAILURE);
	if (pid[i] == 0)
	{
		job->out = -81;
		if (job->redirect)
		{
			ft_redirin(job->redirect, 0);
			ft_redirout(job, 0);
		}
		ft_dup_close(tubo, 1, job->out);
		if (job->command)
			ft_runcmnd(job, ms, 0);
		else
			exit(0);
	}
	else
		ft_dup_close(tubo, 2, job->out);
}

static void	ft_runend(t_coml *job, t_ms *ms, int i)
{
	ms->pid[i] = fork();
	if (ms->pid[i] < 0)
		ft_error_exit("Fork failed:", NO_FORK, EXIT_FAILURE);
	if (ms->pid[i] == 0)
	{
		job->out = -81;
		if (job->redirect)
		{
			ft_redirin(job->redirect, 1);
			ft_redirout(job, 1);
		}
		if (job->command)
			ft_runcmnd(job, ms, 1);
		else
			exit(0);
	}
	else
	{
		ft_waitend(ms->pid[i], ms);
	}
}

static int	ft_job(t_ms *ms)
{
	int		i;
	t_coml	*job;
	pid_t	pid[MAX_ARGS];

	job = ms->cmnd_list;
	i = 0;
	if (ms->cmnd_count == 1 && ft_is_builtin(job) >= 4)
	{
		ms->exit_code = ft_builtin_redir(job);
		if (!ms->exit_code)
			ms->exit_code = ft_execute_built(job, ms, ft_is_builtin(job));
		return (ms->exit_code);
	}
	while (++i < ms->cmnd_count)
	{
		ft_runchild(job, ms, i, pid);
		if (job->next)
			job = job->next;
	}
	ft_runend(job, ms, i);
	ft_reset_dups(ms);
	ft_wait(ms->cmnd_count, pid);
	return (0);
}

//Poner controles de numero de hd
//Controls de pipes?
int	ft_execute(t_ms *ms)
{
	ms->cmnd_count = ft_countcmd(ms->cmnd_list);
	if (!ms->cmnd_count)
		return (0);
	if (ft_search_hd(ms, ms->cmnd_list) != 130)
	{
		signal_init(INTERACTIVE);
		ft_job(ms);
	}
	ft_closer(ms, ms->cmnd_count);
	ft_reset_dups(ms);
	return (0);
}
