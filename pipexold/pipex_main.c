/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:31:47 by fcatala-          #+#    #+#             */
/*   Updated: 2023/06/06 08:44:02 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/libpipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_file[2];
	int	ctr[2];

	if (argc != 5)
		ft_error(MSG_1, 1);
	fd_file[OUT_FILE] = ft_openfile(argv[argc - 1], OUT_FILE, argv[1]);
	if (fd_file[OUT_FILE] < 0)
		ft_error(MSG_3, 1);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		fd_file[IN_FILE] = ft_openfile(argv[1], IN_FILE, argv[1]);
		ctr[1] = 0;
	}
	else
	{
		ctr[1] = 1;
		ft_error(MSG_8, 1);
	}
	ctr[0] = 0;
	while (++ctr[0] <= argc - 4 - ctr[1])
		run_child_1(argv, envp, fd_file, ctr);
	run_child_end(argv, envp, fd_file, argc);
	waitpid(-1, NULL, 0);
	return (0);
}
