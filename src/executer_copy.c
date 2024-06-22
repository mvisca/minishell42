/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/06/21 14:14:10 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Contador de comandos. Inicializa los fd de entrada y salida
static int	ft_countcmd(t_coml *coml)
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

static char	*ft_getcmd(char *cmnd, t_ms *ms, int last)
{
	int		i;
	int		aux;
	char	*out;
	char	**paths;

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

static int	ft_is_builtin(t_coml *aux)
{
	if (!aux->command || !aux->command[0])
		return (0);
	if (ft_strcmp(aux->command[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(aux->command[0], "echo") == 0)
		return (2);
	else if (ft_strcmp(aux->command[0], "env") == 0)
		return (0);
	else if (ft_strcmp(aux->command[0], "export") == 0)
		return (4);
	else if (ft_strcmp(aux->command[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(aux->command[0], "cd") == 0)
		return (6);
	else if (ft_strcmp(aux->command[0], "exit") == 0)
		return (0);
	else
		return (0);
}

static int	ft_execute_built(t_coml *aux, t_ms *ms, int type)
{
	if (type == 1)
		return (builtin_pwd(ms));
	else if (type == 2)
		return (builtin_echo(aux->command));
	else if (type == 3)
		return (0);
	else if (type == 4)
		return (builtin_export(ms, aux));
	else if (type == 5)
		return (builtin_unset(ms, aux));
	else if (type == 6)
		return (builtin_cd(ms, aux->command));
	else
		return (0);
}

static int	ft_isdir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	else
		closedir(dir);
	return (1);
}

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

static void	ft_dup_close(int tubo[2], int pos, int out)
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
		if (job->command && job->command[0])
			ft_runcmnd(job, ms, 0);
		else
			exit(0);
	}
	else
		ft_dup_close(tubo, 2, job->out);
}

static void	ft_waitend(pid_t pid, t_ms *ms)
{
	int	stat;

	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
	{
		ms->exit_code = WEXITSTATUS(stat);
	}
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
		if (job->command && job->command[0])
			ft_runcmnd(job, ms, 1);
		else
			exit(0);
	}
	else
	{
		ft_waitend(ms->pid[i], ms);
	}
}

static void	ft_wait(int count, pid_t pid[MAX_ARGS], t_ms *ms)
{
	int		stat;

	while (--count > 0)
	{
		waitpid(pid[count], &stat, 0);
		if (WIFEXITED(stat))
			printf("Children %d pos %d terminated with status: %d. Check signals\n",
				pid[count], count, WEXITSTATUS(stat));
		else if (WIFSIGNALED(stat))
		{
			printf("Sequence terminated with: %d or %d\n", WIFSIGNALED(stat), g_exit);
			if (WTERMSIG(stat) == SIGINT)
			{
				printf("Exit code will be 130\n");
				ms->exit_code = 130;				
			}
			else if (WTERMSIG(stat) == SIGQUIT)
			{
				ms->exit_code = 131;				
				printf("Quit as 131\n");
			}
		}
	}
}

static void	ft_reset_dups(t_ms *ms)
{
	dup2(ms->init_fd[0], STDIN_FILENO);
	close(ms->init_fd[0]);
	ms->init_fd[0] = dup(STDIN_FILENO);
	dup2(ms->init_fd[1], STDOUT_FILENO);
	close(ms->init_fd[1]);
	ms->init_fd[1] = dup(STDOUT_FILENO);
}

static int	ft_is_quoted(char *eof)
{
	int	quoted;

	quoted = 0;
	if ((eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"')
		|| (eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\''))
		quoted = 1;
	return (quoted);
}

static char	*ft_expand_hd(int quoted, t_ms *ms, char *tmp)
{
	char	*line;

	if (!quoted)
	{
		expander_get_expansion(ms, tmp);
		line = ft_strjoin(ms->strs.new, "\n");
	}
	else
		line = ft_strjoin(tmp, "\n");
	return (line);
}

static void	ft_end_hd(char *tmp, char *eof, int fd, int l)
{
	char	*line;

	if (!tmp && g_exit != 130)
	{
		line = ft_itoa(l);
		tmp = ft_strjoin3(HD_2, eof, HD_3);
		ft_error_noexit(HD_1, line, tmp);
	}
	free(tmp);
	close(fd);
}

static int	ft_write_hd(t_ms *ms, int fd, char *eof)
{
	static int	l = 0;
	char		*tmp;
	char		*line;
	int			quoted;

	quoted = ft_is_quoted(eof);
	eof = expander_filter_quotes(eof);
	signal_init(HEREDOC);
	tmp = readline("> ");
	while (!g_exit)
	{
		++l;
		if (!tmp || !ft_strcmp(eof, tmp))
			break ;
		line = ft_expand_hd(quoted, ms, tmp);
		write(fd, line, ft_strlen(line));
		ms->strs.new = ft_memdel(ms->strs.new);
		free(line);
		free(tmp);
		tmp = readline("> ");
	}
	ft_end_hd(tmp, eof, fd, l);
	return (g_exit);
}

static int	ft_check_hd(t_ms *ms, t_redl *files)
{
	static int	n = 0;
	char		*c;
	int			fd;
	int			i;

	i = 0;
	fd = -1;
	while (fd == -1)
	{
		c = ft_memdel(c);
		c = ft_itoa(n++);
		files->path = ft_strjoin3(".", c, H_FILE);
		if (access(files->path, F_OK) != 0)
			fd = open(files->path, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	free(c);
	signal_init(HEREDOC);
	i = ft_write_hd(ms, fd, files->eof);
	close(fd);
	ms->exit_code = i;
	return (i);
}

static int	ft_search_hd(t_ms *ms, t_coml *job)
{
	t_coml		*coms;
	t_redl		*files;

	coms = job;
	while (coms)
	{
		if (coms->redirect)
		{
			files = coms->redirect;
			while (files)
			{
				if (files->type == DL_REDIRECT)
				{
					files->eof = ft_strdup(files->path);
					if (ft_check_hd(ms, files) == 130)
						return (130);
				}
				files = files->next;
			}
		}
		coms = coms->next;
	}
	return (0);
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
	ft_wait(ms->cmnd_count, pid, ms);
	return (0);
}

//Poner controles de numero de hd
//Controls de pipes?
int	ft_execute(t_ms *ms)
{
	ms->cmnd_count = ft_countcmd(ms->cmnd_list);
	if (ft_search_hd(ms, ms->cmnd_list) != 130)
	{
		signal_init(INTERACTIVE);
		ft_job(ms);
	}
	ft_closer(ms, ms->cmnd_count);
	ft_reset_dups(ms);
	return (0);
}
