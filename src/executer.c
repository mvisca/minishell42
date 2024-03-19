/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/03/19 18:12:22 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_execute(t_ms *ms)
{
	int		i;

	ft_printf("\nEntra en executer\n");
	ms->debu.cmnd_count = ft_countcmd(ms->cmnd_list);
	i = ft_opener(ms, ms->debu.cmnd_count);
	printf("\ni = %d\n", i);
	if (i == 0)
		printf("\n All files opened OK\n");
	ft_closer(ms, ms->debu.cmnd_count);
	ft_printf("\nSale de executer\n");
	return (0);
}
