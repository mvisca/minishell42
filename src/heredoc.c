/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:59:26 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/09 18:40:09 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_expand_hd(int quoted, t_ms *ms, char *tmp)
{
	char	*line;

	if (!quoted)
	{
		expander_get_expansion(ms, tmp, 0);
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
		else
			free(files->path);
	}
	free(c);
	signal_init(HEREDOC);
	i = ft_write_hd(ms, fd, files->eof);
	close(fd);
	ms->exit_code = 130 * i / SIGINT;
	return (ms->exit_code);
}

//mover a parseo
static int	ft_error_nopath(t_coml *coms, t_redl *files)
{
	if (files->next)
		return (ft_error_return(SYNTAX_ONLY, files->next->path, "\n", 2));
	if (!coms->next)
		return (ft_error_return(SYNTAX_ONLY, "'newline'", "\n", 2));
	if (coms->next)
		return (ft_error_return(SYNTAX_ONLY, "'|'", "\n", 2));
	return (8);
}

//numero maximo HD = 16 contar antes de entrar y hasta 1er syntax. exit_code = 2
int	ft_search_hd(t_ms *ms, t_coml *job)
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
				if (!files->path)
				{	
					printf("Next is %d\n", files->type);
					return (ft_error_nopath(coms, files));
				}
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
