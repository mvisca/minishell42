/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/04/27 18:22:15 by fcatala-         ###   ########.fr       */
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
	if (redir == L_REDIRECT)
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

//falta mejorar control de errores
static void	ft_runcmnd(t_coml *job, t_ms *ms)
{
	t_coml	*aux;

	aux = job;
	if (!ft_strchr(aux->command[0], '/'))
		aux->command[0] = ft_getcmd(aux->command[0], ms->envarr);
	if (execve(aux->command[0], aux->command, ms->envarr) == -1)
	{
		printf("\nError in exec\n");
		exit (127);
	}
}

static void	ft_read_heredoc(char *eof, int tubo[2], int init_fd[2])
{
	char	*tmp;
	char	*line;

	close(tubo[0]);
	dup2(init_fd[0], STDIN_FILENO);
	while (1)
	{
		tmp = readline("> ");
		line = ft_strjoin(tmp, "\n");
		if (!line || (!ft_strncmp(eof, tmp, ft_strlen(tmp)) && ft_strlen(line) > 1))
			break ;
		write(tubo[1], line, ft_strlen(line));
		free(tmp);
		free(line);
	}
	free(eof);
	free(tmp);
	close(tubo[1]);
	exit(EXIT_SUCCESS);
}

//mirar prioridad de heredoc
int	ft_heredoc(char *eof, int init_fd[2])
{
	int		tubo[2];
	pid_t	pid;
	int		status;

	if (pipe(tubo) < 0)
		exit (1);
	pid = fork();
	if (pid < 0)
		exit (1);
	if (pid == 0)
	{
		ft_read_heredoc(eof, tubo, init_fd);
	}
	waitpid(pid, &status, 0);
	close(tubo[W_END]);
	dup2(tubo[R_END], STDIN_FILENO);
	close(tubo[R_END]);
	return (0);
}

//falta mejorar control de errores
static void	ft_dup_close(t_coml *job)
{
	if (job->in >= 0)
	{
		if (dup2(job->in, STDIN_FILENO) < 0)
			exit (1);
		close(job->in);
		job->in = -42;
	}
	if (job->out >= 0)
	{
		if (dup2(job->out, STDOUT_FILENO) < 0)
			exit (1);
		close(job->out);
		job->out = -69;
	}
}

//falta mejorar control de errores
static void	ft_redirin(t_coml *job, int init_fd[2])
{
	t_redl	*files;

	files = job->redirect;
	while (files)
	{
		if (files->type == DL_REDIRECT)
			ft_heredoc(files->path, init_fd);
		if (files->type == L_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			if (files->fdes < 0)
			{
				perror(files->path);//chequear comportamiento bash
//				exit (149);
				break ;
			}
			job->in = files->fdes;			
		}
		files = files->next;
	}
}

static void	ft_redirout(t_coml *job)
{
	t_redl	*files;

	files = job->redirect;
	while (files)
	{
		if (files->type == R_REDIRECT || files->type == DR_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			if (files->fdes < 0)
				break ;//va a mantener el ultimo fd valido
			job->out = files->fdes;
		}
		files = files->next;
	}
	if (files && files->fdes < 0)
	{
		perror(files->path);
	}
}

static void	ft_runchild(t_coml *job, t_ms *ms, int num)
{

	if (num == 0)
		close(ms->l_tubo[0]);//no se si hay que reinicializar a negativo
	ft_redirout(job);
	ft_redirin(job, ms->l_tubo);//hay que mirar el tema del HD
	ft_dup_close(job);
	if (job->command && job->command[0])
		ft_runcmnd(job, ms);
	else
		exit(0);//mirar que pasa con este error
}

static int	ft_runend(t_coml *job, t_ms *ms, int i)
{
	ms->pid = fork();
	if (ms->pid < 0)
		exit (1);//comprobar error
	else if (ms->pid == 0)
		ft_runchild(job, ms, i);
	if (ms->cmnd_count > 1 && job->in >= 0)//no se si hay que controlar algo mas
		close(job->in);
	if (ms->l_tubo[0] >= 0)
		close(ms->l_tubo[0]);
	return (0);//acordar valor de retorno a ver
}

static void	ft_wait(t_ms *ms)
{
	int		stat;
	int		i;

	i = 0;
	while (++i <= ms->cmnd_count )
	{
		if (ms->pid == wait(&stat))
		{
			if (WIFEXITED(stat))
				ms->exit_code = WEXITSTATUS(stat);
		}
	}
}

static void	ft_reset_dups(t_ms *ms)
{
	ms->cmnd_list->in = -42;
	ms->cmnd_list->out = -63;
	dup2(ms->std_in, STDIN_FILENO);
	close(ms->std_in);
	ms->std_in = dup(STDIN_FILENO);
	dup2(ms->std_out, STDOUT_FILENO);
	close(ms->std_out);
	ms->std_out = dup(STDOUT_FILENO);
}

static int	ft_job(t_ms *ms)
{
	int		i;
	t_coml	*job;

	i = 0;
	job = ms->cmnd_list;
	while (++i < ms->cmnd_count)
	{
		if (pipe(ms->l_tubo) == -1)
			return (-1);
		job->out = ms->l_tubo[1];
		ms->pid = fork();
		if (ms->pid < 0)
			return (-1);
		if (ms->pid == 0)
			ft_runchild(job, ms, 0);
		close (ms->l_tubo[1]);
		if (job->in >= 0)
			close (job->in);
		if (job->next)
			job = job->next;
		job->in = ms->l_tubo[0];
	}
	ms->exit_code = ft_runend(job, ms, i);
	ft_wait(ms);
	return (0);
}

int	ft_execute(t_ms *ms)
{
	ms->cmnd_count = ft_countcmd(ms->cmnd_list);
	ft_reset_dups(ms);
	ft_job(ms);
	ft_reset_dups(ms);
	ft_closer(ms, ms->cmnd_count);
	return (0);
}
