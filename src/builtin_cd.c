/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:52:47 by fcatala-          #+#    #+#             */
/*   Updated: 2024/06/08 11:31:40 by fcatala-         ###   ########.fr       */
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

static int	ft_mini_cd(char *path, t_ms *ms)
{
	int			out;
	struct stat	stat;

	out = 0;
	if (path[0] == '~')
		path = ft_strjoin(environment_get_value(ms, "HOME"), path + 1);
	lstat(path, &stat);
	out = chdir(path);
	path = getcwd(NULL, 0);
	if (!path)
		return (printf("%s%s%s", NO_CWD, NO_GETCWD, NO_FILE), 0);
	if (access(path, F_OK) == -1)
		return (ft_error_noexit("cd: ", path, NO_FILE), -1);
	if (!S_ISDIR(stat.st_mode))
		return (ft_error_noexit("cd: ", path, IS_NO_DIR), -1);
	if (access(path, X_OK) == -1)
		return (ft_error_noexit("cd: ", path, NO_EXEC), -1);
	free(path);
	return (out);
}

static void	ft_update_oldpwd(t_ms *ms, char *path, char *oldpwd, int i)
{
	environment_update_node(ms, "PWD", ft_strdup(path));
	if (environment_get_value(ms, "OLDPWD") && i == 0)
		environment_update_node(ms, "OLDPWD", ft_strdup(oldpwd));
	else if (!environment_get_value(ms, "OLDPWD") && i == 0)
		environment_add_node(ms, environment_new_node(ms, "OLDPWD", oldpwd));
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
	{
		if (!environment_get_value(ms, "HOME"))
			return (ft_error_noexit(cmnd[0], NULL, NO_HOME), 1);
		i *= chdir(environment_get_value(ms, "HOME"));
	}
	else if (ft_strcmp(cmnd[1], "-") == 0)
	{
		i *= chdir(environment_get_value(ms, "OLDPWD"));
		if (i != 0)
			ft_error_noexit("cd", NULL, NO_OLD);
		else
			printf("%s\n", environment_get_value(ms, "OLDPWD"));
	}
	else
		i *= ft_mini_cd(cmnd[1], ms);
	getcwd(path, sizeof(path));
	ft_update_oldpwd(ms, path, oldpwd, i);
	return (i);
}
