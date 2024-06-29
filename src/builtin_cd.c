/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:52:47 by fcatala-          #+#    #+#             */
/*   Updated: 2024/06/29 10:53:17 by fcatala-         ###   ########.fr       */
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

static int	ft_path_outmax(char *path)
{
	int		i;
	char	**paths;

	paths = ft_split(path, '/');
	i = 0;
	while (paths[i])
	{
		if (ft_strlen(paths[i]) > MAX_NAME)
		{
			ft_freechain(paths);
			return (1);
		}
		i++;
	}
	ft_freechain(paths);
	return (0);
}

static int	ft_mini_cd(char *path, t_ms *ms)
{
	int			out;
	struct stat	stat;

	out = 0;
	if (ft_path_outmax(path))
		return (ft_error_return("cd: ", path, TOO_LONG, -1));
	if (path[0] == '~')
		path = ft_strjoin(environment_get_value(ms, "HOME"), path + 1);
	lstat(path, &stat);
	if (access(path, F_OK) == -1)
		return (ft_error_return("cd: ", path, NO_FILE, -1));
	if (!S_ISDIR(stat.st_mode))
		return (ft_error_return("cd: ", path, IS_NO_DIR, -1));
	if (access(path, X_OK) == -1)
		return (ft_error_return("cd: ", path, NO_EXEC, -1));
	out = chdir(path);
	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error_return(NO_CWD, NO_GETCWD, NO_FILE, 0));
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

static int	ft_cd_to_old(t_ms *ms)
{
	int	i;

	i = chdir(environment_get_value(ms, "OLDPWD"));
	if (i != 0)
		ft_error_noexit("cd", NULL, NO_OLD);
	else
		printf("%s\n", environment_get_value(ms, "OLDPWD"));
	return (i);
}

int	builtin_cd(t_ms *ms, char **cmnd, int i)
{
	char	path[MAX_PATH];
	char	oldpwd[MAX_PATH];

	if (ft_tablen(cmnd) > 2)
		return (ft_error_return("cd", NULL, MANY, 1));
	if (cmnd[1] && !cmnd[1][0])
		return (0);
	getcwd(oldpwd, sizeof(oldpwd));
	if (!cmnd[1] || cmnd[1][0] == '\0' || ft_strcmp(cmnd[1], "~") == 0)
	{
		if (!environment_get_value(ms, "HOME"))
			return (ft_error_noexit(cmnd[0], NULL, NO_HOME), 1);
		i *= chdir(environment_get_value(ms, "HOME"));
	}
	else if (ft_strcmp(cmnd[1], "-") == 0)
		i *= ft_cd_to_old(ms);
	else
		i *= ft_mini_cd(cmnd[1], ms);
	getcwd(path, sizeof(path));
	if (cmnd[1] && !ft_strcmp(cmnd[1], "//"))
		ft_update_oldpwd(ms, "//", oldpwd, i);
	else
		ft_update_oldpwd(ms, path, oldpwd, i);
	return (i);
}
