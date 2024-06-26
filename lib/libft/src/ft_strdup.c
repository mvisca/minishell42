/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   ft_strdup.c										:+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: mvisca-g <mvisca-g@student.42barcel>	   +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2023/04/24 11:25:25 by mvisca-g		  #+#	#+#			      */
/*   Updated: 2023/05/15 16:38:58 by mvisca-g         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	if (!s || !*s)
		len = 0;
	else
		len = ft_strlen((char *)s);
	dup = (char *) malloc (sizeof(char) * (len + 1));
	if (dup && s && *s)
	{
		i = 0;
		while (s && *(s + i))
		{
			*(dup + i) = *(s + i);
			i++;
		}
		*(dup + i) = '\0';
	}
	return (dup);
}
