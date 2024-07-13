/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:03:28 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/13 15:50:48 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//prueba de cambios de permisos	
int	ft_openfile(char *file, int redir)
{
	int	fd;

	fd = -1;
	if (redir == L_REDIRECT || redir == DL_REDIRECT)
		fd = open(file, O_RDONLY, 0644);
	else if (redir == R_REDIRECT)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (redir == DR_REDIRECT)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	return (fd);
}

int	ft_closer(t_ms *ms, int i)
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
				{
					unlink(files->path);
					files->path = ft_memdel(files->path);
				}
				files = files->next;
			}
		}
		aux = aux->next;
	}
	return (0);
}

void	ft_redirin(t_redl	*files, int last)
{
	while (files)
	{
		files->path = expander_filter_quotes(files->path);
		if (files->type == L_REDIRECT || files->type == DL_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			if (files->fdes < 0)
				break ;
			if (dup2(files->fdes, STDIN_FILENO) < 0)
				ft_error_exit(DUP_FAIL, strerror(errno), EXIT_FAILURE);
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

void	ft_redirout(t_coml *job, int last)
{
	t_redl	*files;

	files = job->redirect;
	while (files)
	{
		files->path = expander_filter_quotes(files->path);
		if (files->type == R_REDIRECT || files->type == DR_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			job->out = files->fdes;
			if (files->fdes < 0)
				break ;
			if (dup2(files->fdes, STDOUT_FILENO) < 0)
				ft_error_exit(DUP_FAIL, strerror(errno), EXIT_FAILURE);
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
