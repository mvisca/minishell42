/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/05/22 22:58:08 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
static void ft_mini_ls()
{
	DIR				*dir;
	struct dirent	*entry;
	char	path[MAX_PATH];

	getcwd(path,sizeof(path));
	dir = opendir(path);
	printf("Content of current directory: %s\n", path);
	entry = readdir(dir);
	while (entry != NULL)
	{
		printf("%s\n", entry->d_name);
		entry = readdir(dir)
	}
	closedir(dir);

}
*/
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

//Inicio de executer
//v_01 : recorrer envp como pipex (while)
//v_02 : out = getenv("PATH");
//v_03 : out = environment_get_value(ms, "PATH")
static char	*ft_getcmd(char *cmnd, t_ms *ms)
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
	}
	if (aux == -1)
		out = ft_strjoin("/", cmnd);
	ft_freechain(paths);
	return (out);
}

static int	ft_mini_cd(char *path)
{
	int	out;

	out = 0;
	if (path[0] == '~')
		path = ft_strjoin(getenv("HOME"), path + 1);
	out = chdir(path);
	if (access(path, F_OK) == -1)
		ft_error_noexit("cd", NO_FILE);
	else if (access(path, X_OK) == -1)
		ft_error_noexit("cd", NO_EXEC);
	return (out);
}

static int	builtin_cd(t_ms *ms, char **cmnd)
{
	char	path[MAX_PATH];
	char	oldpwd[MAX_PATH];
	char	*tmp;
	int		i;

	i = -1;
	getcwd(oldpwd, sizeof(oldpwd));
	if (!cmnd[1] || cmnd[1][0] == '\0' || ft_strcmp(cmnd[1], "~") == 0)
		i *= chdir(getenv("HOME"));
	else if (ft_strcmp(cmnd[1], "-") == 0)
	{
		i *= chdir(environment_get_value(ms, "OLDPWD"));
		if (i != 0)
			ft_error_noexit("cd", NO_OLD);
		else
			printf("%s\n", environment_get_value(ms, "OLDPWD"));
	}
	else
		i *= ft_mini_cd(cmnd[1]);
	getcwd(path, sizeof(path));
	tmp = ft_strdup(path);
	environment_update_node(ms, "PWD", tmp);
	if (environment_get_value(ms, "OLDPWD") && i == 0)
	{
		tmp = ft_strdup(oldpwd);
		environment_update_node(ms, "OLDPWD", tmp);
	}
	else if (!environment_get_value(ms, "OLDPWD") && i == 0)
		environment_add_node(ms, environment_new_node(ms, "OLDPWD", oldpwd));
	return (i);
}

//ok in pipe and at any place: pwd, echo, env
//only solo: cd, exit
//only at the end? or solo: export unset
static int	ft_is_builtin(t_coml *aux)
{
	if (ft_strcmp(aux->command[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(aux->command[0], "echo") == 0)
		return (2);
	else if (ft_strcmp(aux->command[0], "env") == 0)
		return (0);
	else if (ft_strcmp(aux->command[0], "export") == 0)
		return (0);
	else if (ft_strcmp(aux->command[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(aux->command[0], "cd") == 0)
		return (6);
	else if (ft_strcmp(aux->command[0], "exit") == 0)
		return (0);
	else
		return (0);
}

static int	ft_execute_built(t_coml *aux, t_ms *ms, int type)
//static int	ft_execute_built(t_coml *aux, t_ms *ms, int last, int type)
{
	if (type == 1)
		return (builtin_pwd(ms));
	else if (type == 2)
		return (builtin_echo(aux->command));
	else if (type == 6)
		return (builtin_cd(ms, aux->command));
	else
		return (0);
}

//v_01 : aux->command[0] = ft_getcmd(aux->command[0], ms->envarr);
//v_02 : aux->command[0] = ft_getcmd(aux->command[0]);
//v_03 : aux->command[0] = ft_getcmd(aux->command[0], ms);
static void	ft_runcmnd(t_coml *job, t_ms *ms, int last)
{
	t_coml	*aux;
	int		i;

	aux = job;
	i = ft_is_builtin(aux);
	if (i)
	{
		exit (ft_execute_built(aux, ms, i) * last);
	}
	else if (!ft_strchr(aux->command[0], '/'))
	{
		aux->command[0] = ft_getcmd(aux->command[0], ms);
		i = 1;
	}
	else if (opendir(aux->command[0]) != NULL)
		ft_error_exit(aux->command[0], IS_DIR, last * EXIT_DENIED);
	else if (access(aux->command[0], F_OK) != 0)
		ft_error_exit(aux->command[0], NO_FILE, last * EXIT_NOTFOUND);
	else if (access(aux->command[0], X_OK) != 0)
		ft_error_exit(aux->command[0], NO_EXEC, last * EXIT_DENIED);
	if (execve(aux->command[0], aux->command, ms->envarr) == -1)
		ft_error_exit(aux->command[0] + i, NO_FOUND, last * EXIT_NOTFOUND);
}

//falta mejorar control de errores
static void	ft_dup_close(int tubo[2], int pos, int out)
{
	if (pos == 1)
	{
		close(tubo[R_END]);
		if (out < 0)
		{
			if (dup2(tubo[W_END], STDOUT_FILENO) < 0)
				exit (1);
		}
		close(tubo[W_END]);
	}
	if (pos == 2)
	{
		close(tubo[W_END]);
		if (dup2(tubo[R_END], STDIN_FILENO) < 0)
			exit (1);
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
/*
//ascending mode works fine as desdending mode
static void	ft_wait(int count, pid_t pid[MAX_ARGS])
{
	int		stat;
	int		i;

	i = 0;
	while (++i < count)
	{
		waitpid(pid[i], &stat, 0);
		if (WIFEXITED(stat))
				printf("Children %d pos %d end status: %d\n", 
				pid[i], i, WEXITSTATUS(stat));
	}
}
*/

//			printf("Child %d %s pos %d end status: %d\n", ms->pid[i], 
//			job->command[0], i, WEXITSTATUS(stat));
static void	ft_runend(t_coml *job, t_ms *ms, int i)
{
	int		stat;

	stat = 0;
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
		waitpid(ms->pid[i], &stat, 0);
		if (WIFEXITED(stat))
			ms->exit_code = WEXITSTATUS(stat);
	}
}

//descending  mode works fine as asdending mode
//check for other exit cases
static void	ft_wait(int count, pid_t pid[MAX_ARGS])
{
	int		stat;

	while (--count > 0)
	{
		waitpid(pid[count], &stat, 0);
		if (WIFEXITED(stat))
			printf("Children %d pos %d terminated with status: %d\n",
				pid[count], count, WEXITSTATUS(stat));
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

static void	ft_write_hd(t_ms *ms, int fd, char *eof)
{
	char	*tmp;
	char	*line;

//	tmp = readline("> ");
	while (1)
	{
		tmp = readline("> ");
		if (!ft_strncmp(eof, tmp, ft_strlen(tmp)))
			break ;
		expander_get_expansion(ms, tmp);
		expander_filter_quotes(ms->strs.new);
		line = ft_strjoin(ms->strs.new, "\n");
		write(fd, line, ft_strlen(line));
		free(ms->strs.new);
		ms->strs.new = NULL;
		free(line);
		free(tmp);
	}
	free(tmp);
	close(fd);
}

//falta control errores hd
static void	ft_check_hd(t_ms *ms, t_redl *files)
{
	static int	n = 0;
	char		*c;
	int			fd;

	fd = -1;
	while (fd == -1)
	{
		c = ft_itoa(n++);
		files->path = ft_strjoin3(".", c, H_FILE);
		if (access(files->path, F_OK) != 0)
		{
			fd = open(files->path, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
	}
	ft_write_hd(ms, fd, files->eof);
	close(fd);
	free(c);
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
					ft_check_hd(ms, files);
				}
				files = files->next;
			}
		}
		coms = coms->next;
	}
	return (1);
}

static int	ft_job(t_ms *ms)
{
	int		i;
	t_coml	*job;
	pid_t	pid[MAX_ARGS];

	job = ms->cmnd_list;
	ft_reset_dups(ms);
	ft_search_hd(ms, job);
	i = ft_is_builtin(job);
	if (ms->cmnd_count == 1 && i >= 6)
	{
		ms->exit_code = ft_execute_built(job, ms, i);
		return (ms->exit_code);
	}
	i = 0;
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

int	ft_execute(t_ms *ms)
{
	ms->cmnd_count = ft_countcmd(ms->cmnd_list);
	ft_job(ms);
	printf("Exit code: %d\n", ms->exit_code);
	ft_closer(ms, ms->cmnd_count);
	ft_reset_dups(ms);
	return (0);
}
