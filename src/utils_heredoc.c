/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:59:02 by fcatala-          #+#    #+#             */
/*   Updated: 2024/07/15 18:06:45 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_maxhd(t_coml *coms)
{
	int		i;
	t_redl	*files;

	i = 0;
	while (coms && i < MAX_HDS)
	{
		if (coms->redirect)
		{
			files = coms->redirect;
			while (files)
			{
				if (!files->path)
					return (ft_error_return(SYNTAX_ONLY, "path", "\n", 2));
				if (files->type == DL_REDIRECT)
					i++;
				files = files->next;
			}
		}
		coms = coms->next;
	}
	if (i >= MAX_HDS)
		return (ft_error_return(TOO_HD, NULL, NULL, 2));
	return (0);
}
