/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:36:30 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/07/25 14:03:36 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstnew(int *content)
{
	t_list	*new;

	new = (t_list *) malloc (sizeof(t_list));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}
