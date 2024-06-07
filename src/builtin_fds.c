/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:03:28 by fcatala-          #+#    #+#             */
/*   Updated: 2024/05/25 13:41:31 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_redirin_built(t_redl	*files)
{
	while (files)
	{
		if (files->type == L_REDIRECT || files->type == DL_REDIRECT)
		{
			files->fdes = ft_openfile(files->path, files->type);
			if (files->fdes < 0)
				break ;
			if (dup2(files->fdes, STDIN_FILENO) < 0)
				return (ft_error_noexit(DUP_FAIL, strerror(errno)), 1);
			close(files->fdes);
		}
		files = files->next;
	}
	if (files && files->fdes < 0)
	{
		if (access(files->path, F_OK) != 0)
			ft_error_noexit(files->path, NO_FILE);
		else if (access(files->path, R_OK) != 0)
			ft_error_noexit(files->path, NO_EXEC);
		return (1);
	}
	return (0);
}

static int	ft_redirout_built(t_coml *job)
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
				return (ft_error_noexit(DUP_FAIL, strerror(errno)), 1);
			close(files->fdes);
		}
		files = files->next;
	}
	if (files && files->fdes < 0)
	{
		ft_putstr_fd(MINI, 2);
		perror(files->path);
		return (1);
	}
	return (0);
}

int	ft_builtin_redir(t_coml *job)
{
	if (ft_redirin_built(job->redirect))
		return (1);
	else if (ft_redirout_built(job))
		return (1);
	return (0);
}
