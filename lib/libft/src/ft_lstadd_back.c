/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:32:52 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/07/08 17:09:58 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*tmp;

	if (list && !(*list))
	{
		*list = new;
		return ;
	}
	tmp = ft_lstlast(*list);
	tmp->next = new;
}
