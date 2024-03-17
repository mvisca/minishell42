/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:35:37 by fcatala-          #+#    #+#             */
/*   Updated: 2024/03/17 11:02:03 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int ft_openfile(char *file, int redir)
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

static int ft_countcmd(t_coml *coml)
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

int	ft_execute(t_ms *ms)
{
	t_coml	*aux;
	t_redl	*files;

	ft_printf("\nEntra en executer\n");
	ms->debu.cmnd_count = ft_countcmd(ms->cmnd_list);
	printf("\nHay %d comandos\n", ms->debu.cmnd_count);
	aux = ms->cmnd_list;
	if (aux->redirect)
	{
		files = aux->redirect;
		while (files)
		{
			files->fdes = ft_openfile(files->path, files->type);
			printf("\nFile %s opened as %d\n", files->path, files->fdes);
			files = files->next;
		}
		files = aux->redirect;
		while (files)
		{
			if (files->fdes > 0)
			{
				close(files->fdes);
				ft_printf("\nFile %s closed\n", files->path);
			}
			else 
				ft_printf("\nFile %s generated an error\n", files->path);
			files = files->next;
		}
	}
	ft_printf("\nSale de executer\n");
	return (0);
}
