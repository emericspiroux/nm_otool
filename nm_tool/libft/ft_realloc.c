/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/11 14:54:56 by rbenjami          #+#    #+#             */
/*   Updated: 2013/12/27 15:08:52 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	size_t	len;
	void	*new;

	new = NULL;
	len = 0;
	size = 0;
	if (ptr != NULL)
	{
		len = ft_strlen((char *)ptr);
		size += len;
		if ((new = ft_memalloc(size + 1)) == NULL)
			return (NULL);
		ft_memcpy(new, ptr, len);
		ft_memdel(&ptr);
	}
	else
		new = ft_memalloc(size + 1);
	return (new);
}
