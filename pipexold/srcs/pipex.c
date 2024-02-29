/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:18:32 by fcatala-          #+#    #+#             */
/*   Updated: 2023/06/06 08:43:36 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

void	run_cmd(char *argv, char **envp, int fd_file, int ctr)
{
	char	**cmd;

	if (fd_file < 0 && ctr == 1)
		exit(0);
	cmd = get_cmd(argv, envp);
	if (execve(cmd[0], cmd, envp) == -1)
		ft_err_m(ft_strjoin(ft_split(argv, ' ')[0], MSG_7), 127);
}

void	run_child_1(char **argv, char **envp, int *fd_file, int *ctr)
{
	int		tube[2];
	pid_t	pid;

	if (fd_file[IN_FILE] > 0 && ctr[0] == 1)
		dup2(fd_file[IN_FILE], STDIN_FILENO);
	if (pipe(tube) < 0)
		ft_error(MSG_5, 1);
	pid = fork();
	if (pid < 0)
		ft_error(MSG_6, 1);
	if (pid == 0)
	{
		close(tube[R_END]);
		dup2(tube[W_END], STDOUT_FILENO);
		close(tube[W_END]);
		run_cmd(argv[ctr[0] + ctr[1] + 1], envp, fd_file[IN_FILE], ctr[0]);
	}
	else
	{
		close(tube[W_END]);
		dup2(tube[R_END], STDIN_FILENO);
		close(tube[R_END]);
	}
}

void	run_child_end(char **argv, char **envp, int *fd_file, int argc)
{
	char	**cmd;

	if (fd_file[IN_FILE] > 0)
		close(fd_file[IN_FILE]);
	dup2(fd_file[OUT_FILE], STDOUT_FILENO);
	close(fd_file[OUT_FILE]);
	cmd = get_cmd(argv[argc - 2], envp);
	if (execve(cmd[0], cmd, envp) == -1)
	{
		if (access(cmd[0], X_OK) < 0 && !access(cmd[0], F_OK))
			ft_err_m(ft_strjoin(ft_split(argv[argc - 2], ' ')[0], MSG_7), 126);
		ft_err_m(ft_strjoin(ft_split(argv[argc - 2], ' ')[0], MSG_7), 127);
	}
}
