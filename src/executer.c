/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/03/26 17:51:52 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_freechain(char **chain)
{
	int	i;

	i = -1;
	while (chain[++i])
		free(chain[i]);
	free(chain);
}

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

static int	ft_openfile(char *file, int redir)
{
	int	fd;

	fd = -1;
	if (redir == L_REDIRECT)
		fd = open(file, O_RDONLY, 0644);
	else if (redir == R_REDIRECT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (redir == DR_REDIRECT)
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	return (fd);
}

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

static int	ft_opener(t_ms *ms, int i)
{
	t_coml	*aux;
	t_redl	*files;

	aux = ms->cmnd_list;
	while (i-- > 0)
	{
		if (aux->redirect)
		{
			files = aux->redirect;
			while (files)
			{
				files->fdes = ft_openfile(files->path, files->type);
				if (files->fdes > 0)
					files = files->next;
				else
				{
					perror(files->path);
					i = -1;
					break ;
				}
			}
		}
		aux = aux->next;
	}
	return (i + 1);
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

static void	ft_runcmnd(t_coml *job, t_ms *ms)
{
	t_coml	*aux;

	aux = job;
	if (!ft_strchr(aux->command[0], '/'))
		aux->command[0] = ft_getcmd(aux->command[0], ms->envarr);
	if (execve(aux->command[0], aux->command, ms->envarr) == -1)
		printf("\nError in exec\n");
}

static void	ft_runchild(t_coml *job, t_ms *ms)
{
	int		tubo[2];
	t_redl	*aux_redl;
	pid_t	pid;

	if (job->redirect)
	{
		aux_redl = job->redirect;
		while (aux_redl)
		{
			if (aux_redl->type == L_REDIRECT)
				dup2(aux_redl->fdes, STDIN_FILENO);
			if (aux_redl->type == R_REDIRECT || aux_redl->type == DR_REDIRECT)
				dup2(aux_redl->fdes, STDOUT_FILENO);
			aux_redl = aux_redl->next;
		}
	}
	if (pipe(tubo) < 0)
		printf("Errorrrrrr\n\n");//
	pid = fork();
	if (pid < 0)
		printf("What a forrrrk\n\n");///
	if (pid == 0)
	{
		close(tubo[R_END]);
		dup2(tubo[W_END], STDOUT_FILENO);
		close(tubo[W_END]);
		ft_runcmnd(job, ms);
	}
	else
	{
		close(tubo[W_END]);
		dup2(tubo[R_END], STDIN_FILENO);
		close(tubo[R_END]);
	}
}

static void	ft_runend(t_coml *job, t_ms *ms)
{
	t_redl	*aux_redl;

	if (job->redirect)
	{
		aux_redl = job->redirect;
		while (aux_redl)
		{
			if (aux_redl->type == L_REDIRECT)
				dup2(aux_redl->fdes, STDIN_FILENO);
			if (aux_redl->type == R_REDIRECT || aux_redl->type == DR_REDIRECT)
				dup2(aux_redl->fdes, STDOUT_FILENO);
			aux_redl = aux_redl->next;
		}
	}
	ft_runcmnd(job, ms);
}

static int	ft_job(t_ms *ms)
{
	int		i;
	t_coml	*job;

	i = 0;
	job = ms->cmnd_list;
	while (++i < ms->debu.cmnd_count)
	{
		ft_runchild(job, ms);
		printf("\nChild %d done\n", i);
		if (job->next)
			job = job->next;
	}
	printf("HOLA PAPI\n");//
	ft_runend(job, ms);
	printf("HOLA PAPI 2\n");//
	waitpid(-1, NULL, 0);
	printf("FIN");
	return (0);
}

int	ft_execute(t_ms *ms)
{
	ft_printf("\nEntra en executer\n");//
	ms->debu.cmnd_count = ft_countcmd(ms->cmnd_list);
	if (ft_opener(ms, ms->debu.cmnd_count) == 0)
	{
		ft_job(ms);
	}
	else
		printf("\nError in files\n");//
	ft_closer(ms, ms->debu.cmnd_count);
	ft_printf("\nSale de executer\n");//
	return (0);
}
