/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:18:09 by fcatala-          #+#    #+#             */
/*   Updated: 2023/06/06 19:11:31 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	ft_error(char *msg, int err)
{
	perror(msg);
	exit(err);
	return (err);
}

int	ft_err_m(char *msg, int err)
{
	ft_putstr_fd(ft_strjoin("pipex: ", msg), 2);
	exit(err);
	return (err);
}

int	ft_openfile(char *file, int mode, char *infile)
{
	int	fd;

	fd = -1;
	if (mode == IN_FILE)
	{
		fd = open(file, O_RDONLY, 0644);
		if (fd < 0)
			perror(ft_strjoin("pipex: ", file));
	}
	else if (mode == OUT_FILE)
	{
		if (!ft_strncmp(infile, "here_doc", ft_strlen(file)))
			fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (mode == HERE_DOC)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			perror(ft_strjoin("pipex: ", file));
	}
	return (fd);
}

static int	ft_chk_break(char *in, char *argv)
{
	int	out;

	out = 0;
	if (!ft_strncmp(in, argv, ft_strlen(in) - 1) && (ft_strlen(in) - 1 > 0))
		out = 1;
	if ((ft_strlen(in) - 1 == 0) && ft_strlen(argv) == 0)
		out = 1;
	return (out);
}

int	ft_here_doc(char **argv)
{
	int		fd[2];
	char	*input;

	fd[0] = ft_openfile(H_FILE, HERE_DOC, argv[1]);
	if (fd[0] < 0)
		return (fd[0]);
	fd[1] = 0;
	while (fd[1] == 0)
	{
		write(1, "heredoc> ", 9);
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			close(fd[0]);
			unlink(H_FILE);
			return (-1);
		}
		if (ft_chk_break(input, argv[2]) == 1)
			fd[1] = 1;
		if (fd[1] == 0)
			write(fd[0], input, ft_strlen(input));
	}
	close (fd[0]);
	fd[0] = ft_openfile(H_FILE, IN_FILE, argv[1]);
	return (fd[0]);
}
