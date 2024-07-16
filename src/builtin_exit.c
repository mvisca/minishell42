/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:11:26 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/16 19:43:18 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//mirar caso exit --
static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (!ft_strlenp(str))
		return (0);
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		else if (ft_isspace(str[i]))
		{
			while (ft_isspace(str[i]) && str[i])
				++i;
			if (str[i])
				return (0);
			return (1);
		}
		++i;
	}
	return (1);
}

static long	long int	ft_atolp(char *str, int *ok, int i, int sign)
{
	unsigned long long	num;

	num = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign -= 2 * (str[i] == '-');
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		if ((num * 10 + str[i] - '0') <= (ULLONG_MAX / 2 + (sign == -1)))
		{
			num = (num * 10) + str[i] - '0';
			i++;
		}
		else
		{
			*ok = 0;
			break ;
		}
	}
	return ((num * sign));
}

static unsigned char	full_exit(t_ms *ms, unsigned int code, int show)
{
	if (show)
		write(2, "exit\n", 5);
	free(ms->line);
	ms->line = NULL;
	utils_free_ms(ms, TRUE);
	exit (code);
}

unsigned char	builtin_exit(t_ms *ms, char **cmnd)
{
	int	ok;

	ok = 1;
	if (ft_tablen(cmnd) == 1 && ms->cmnd_count == 1)
		return (full_exit(ms, ms->exit_code, 1));
	if (ft_isnum(cmnd[1]))
	{
		if (ft_tablen(cmnd) > 2)
		{
			ft_putstr_fd("exit\n", 2);
			return (ft_error_return(cmnd[0], NULL, MANY, 2));
		}
		ms->exit_code = (unsigned char)(ft_atolp(cmnd[1], &ok, 0, 1));
		if (ms->cmnd_count == 1 && ok)
			return (full_exit(ms, ms->exit_code, 1));
		if (ms->cmnd_count > 1 && ok)
			return (ms->exit_code);
	}
	if (ms->cmnd_count > 1)
		return (ft_error_return(cmnd[0], cmnd[1], NUMERIC, 2));
	ft_putstr_fd("exit\n", 2);
	ft_error_return("exit: ", cmnd[1], NUMERIC, 2);
	return (full_exit(ms, 2, 0));
}
