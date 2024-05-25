/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:52:47 by fcatala-          #+#    #+#             */
/*   Updated: 2024/05/25 13:11:22 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
static void ft_mini_ls()
{
	DIR				*dir;
	struct dirent	*entry;
	char	path[MAX_PATH];

	getcwd(path,sizeof(path));
	dir = opendir(path);
	printf("Content of current directory: %s\n", path);
	entry = readdir(dir);
	while (entry != NULL)
	{
		printf("%s\n", entry->d_name);
		entry = readdir(dir)
	}
	closedir(dir);

}
*/

static int	ft_mini_cd(char *path)
{
	int	out;

	out = 0;
	if (path[0] == '~')
		path = ft_strjoin(getenv("HOME"), path + 1);
	out = chdir(path);
	if (access(path, F_OK) == -1)
		ft_error_noexit("cd", NO_FILE);
	else if (access(path, X_OK) == -1)
		ft_error_noexit("cd", NO_EXEC);
	return (out);
}

//eliminated lines
//	char	*tmp;
//	tmp = ft_strdup(path);
//	tmp = ft_strdup(oldpwd);
int	builtin_cd(t_ms *ms, char **cmnd)
{
	char	path[MAX_PATH];
	char	oldpwd[MAX_PATH];
	int		i;

	i = -1;
	getcwd(oldpwd, sizeof(oldpwd));
	if (!cmnd[1] || cmnd[1][0] == '\0' || ft_strcmp(cmnd[1], "~") == 0)
		i *= chdir(environment_get_value(ms, "HOME"));
	else if (ft_strcmp(cmnd[1], "-") == 0)
	{
		i *= chdir(environment_get_value(ms, "OLDPWD"));
		if (i != 0)
			ft_error_noexit("cd", NO_OLD);
		else
			printf("%s\n", environment_get_value(ms, "OLDPWD"));
	}
	else
		i *= ft_mini_cd(cmnd[1]);
	getcwd(path, sizeof(path));
	environment_update_node(ms, "PWD", ft_strdup(path));
	if (environment_get_value(ms, "OLDPWD") && i == 0)
		environment_update_node(ms, "OLDPWD", ft_strdup(oldpwd));
	else if (!environment_get_value(ms, "OLDPWD") && i == 0)
		environment_add_node(ms, environment_new_node(ms, "OLDPWD", oldpwd));
	return (i);
}
