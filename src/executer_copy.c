/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/05/08 17:11:31 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Salida limpia de un char **
static void	ft_freechain(char **chain)
{
	int	i;

	i = -1;
	while (chain[++i])
		free(chain[i]);
	free(chain);
}

//Utils de strings en executer
static int	ft_strlenp(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strcat(char *dest, const char *add)
{
	int	d;
	int	i;

	i = -1;
	if (!add)
		return (dest);
	d = ft_strlenp(dest);
	while (add[++i])
		dest[d + i] = add[i];
	dest[d + i] = '\0';
	return (dest);
}

static char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	int		len;
	char	*out;

	len = ft_strlenp(str1) + ft_strlenp(str2) + ft_strlenp(str3);
	out = malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[0] = '\0';
	ft_strcat(out, str1);
	ft_strcat(out, str2);
	ft_strcat(out, str3);
	return (out);
}

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

//Gestion de ficheros
static int	ft_openfile(char *file, int redir)
{
	int	fd;

	fd = -1;
	if (redir == L_REDIRECT || redir == DL_REDIRECT)
		fd = open(file, O_RDONLY, 0644);
	else if (redir == R_REDIRECT)
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (redir == DR_REDIRECT)
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	return (fd);
}

static int	ft_closer(t_ms *ms, int i)
{
	t_coml	*aux;
	t_redl	*files;

	aux = ms->cmnd_list;
	while (i--)
	{
		if (aux->redirect)
		{
			files = aux->redirect;
			while (files)
			{
				if (files->fdes > 0)
					close(files->fdes);
				if (files->type == DL_REDIRECT)
					unlink(files->path);
				files = files->next;
			}
		}
		aux = aux->next;
	}
	return (0);
}

//Inicio de executer
static char	*ft_getcmd(char *cmnd, char **envp)
{
	int		i;
	int		aux;
	char	*cmd;
	char	**paths;

	i = 0;
	cmd = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		cmd = ft_strdup("Error no path\n");//
		return (cmd);
	}
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	aux = -1;
	while (aux == -1 && paths[++i])
	{
		if (cmd)
			free(cmd);
		cmd = ft_strjoin3(paths[i], "/", cmnd);
		aux = access(cmd, F_OK);
	}
	if (aux == -1)
	{
		free(cmd);
		cmd = ft_strjoin("/", cmnd);
	}
	ft_freechain(paths);
	return (cmd);
}

static void	ft_runcmnd(t_coml *job, t_ms *ms, int last)
{
	t_coml	*aux;
	int		i;

	aux = job;
	i = 0;
	if (!ft_strchr(aux->command[0], '/'))
	{
		aux->command[0] = ft_getcmd(aux->command[0], ms->envarr);
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

//falta mejorar control de errores
static void	ft_redirin(t_redl	*files, int last)
{
	while (files)
	{
		if (files->type == L_REDIRECT || files->type == DL_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			if (files->fdes < 0)
				break ;
			if (dup2(files->fdes, STDIN_FILENO) < 0)
				exit (1);
			close(files->fdes);
		}
		files = files->next;
	}
	if (files && files->fdes < 0)
	{
		if (access(files->path, F_OK) != 0)
			ft_error_exit(files->path, NO_FILE, 1 * last);
		else if (access(files->path, R_OK) != 0)
			ft_error_exit(files->path, NO_EXEC, 1 * last);
	}
}

static void	ft_redirout(t_coml *job, int last)
{
	t_redl	*files;

	files = job->redirect;
	while (files)
	{
		if (files->type == R_REDIRECT || files->type == DR_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			job->out = files->fdes;
			if (files->fdes < 0)
				break ;
			if (dup2(files->fdes, STDOUT_FILENO) < 0)
				exit (1);
			close(files->fdes);
		}
		files = files->next;
	}
	if (files && files->fdes < 0)
	{
		ft_putstr_fd(MINI, 2);
		perror(files->path);
		exit (1 * last);
	}
}

static void	ft_runchild(t_coml *job, t_ms *ms, int i, pid_t pid[MAX_ARGS])
{
	int		tubo[2];

	if (pipe(tubo) < 0)
		exit (1);//perror("pipe"); exit (EXIT_FAILURE);
	pid[i] = fork();
	if (pid[i] < 0)
		exit (1);//perror("fork");exit(EXIT_FAILURE);
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
				printf("Children %d pos %d end status: %d\n", pid[i], i, WEXITSTATUS(stat));
	}
}
*/

static void	ft_runend(t_coml *job, t_ms *ms, int i)
{
	int		stat;

	stat = 0;
	ms->pid[i] = fork();
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
		{
			ms->exit_code = WEXITSTATUS(stat);
			printf("Child %d %s pos %d end status: %d\n", ms->pid[i], job->command[0], i, WEXITSTATUS(stat));
		}
	}
}

//descending  mode works fine as asdending mode
static void	ft_wait(int count, pid_t pid[MAX_ARGS])
{
	int		stat;

	while (--count > 0)
	{
		waitpid(pid[count], &stat, 0);
		if (WIFEXITED(stat))
			printf("Children %d pos %d terminated with status: %d\n", pid[count], count, WEXITSTATUS(stat));
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

static void	ft_write_hd(int fd, char *eof)
{
	char	*tmp;
	char	*line;

	while (1)
	{
		tmp = readline("> ");
		line = ft_strjoin(tmp, "\n");
		if (!line || (!ft_strncmp(eof, tmp, ft_strlen(tmp))
				&& ft_strlen(line) > 1))
			break ;
		write(fd, line, ft_strlen(line));
		free(tmp);
		free(line);
	}
	free(tmp);
	close(fd);
}

static void	ft_check_hd(t_redl *files)
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
	ft_write_hd(fd, files->eof);
	close(fd);
	free(c);
}

static int	ft_search_hd(t_coml *job)
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
					ft_check_hd(files);
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

	i = 0;
	job = ms->cmnd_list;
	ft_reset_dups(ms);
	ft_search_hd(job);
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
