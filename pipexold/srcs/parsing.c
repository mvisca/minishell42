/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:34:50 by fcatala-          #+#    #+#             */
/*   Updated: 2023/10/26 10:35:45 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	ft_end_quote(char *aux, int i, char tmp)
{
	++i;
	while (aux[i] != tmp && aux[i])
		i++;
	return (i);
}

char	**ft_split_cmd(char *argv)
{
	int		i;
	char	tmp;
	char	*aux;

	aux = ft_strdup(argv);
	i = 0;
	while (aux[i])
	{
		if (aux[i] == 39 || aux[i] == 34)
		{
			tmp = aux[i];
			aux[i] = 32;
			i = ft_end_quote(aux, i, tmp);
			if (aux[i])
			{
				aux[i] = 32;
				i++;
			}
		}
		if (aux[i] == 32)
			aux[i] = 16;
		if (aux[i])
			i++;
	}
	return (ft_split(aux, 16));
}

char	**get_cmd(char *argv, char **envp)
{
	int		i;
	int		aux;
	char	*tmp;
	char	**cmd;
	char	**paths;

	cmd = ft_split_cmd(argv);
	if (ft_strchr(cmd[0], '/'))
		return (cmd);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':');
	else
		paths = ft_split(DEF_PATH, ':');
	i = -1;
	aux = -1;
	while (aux == -1 && paths[++i])
		aux = access(ft_strjoin(ft_strjoin(paths[i], "/"), cmd[0]), F_OK);
	tmp = ft_strdup(cmd[0]);
	cmd[0] = ft_strjoin(ft_strjoin(paths[i], "/"), tmp);
	if (aux == -1)
		cmd[0] = ft_strjoin("/", tmp);
	return (cmd);
}
