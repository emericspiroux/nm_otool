/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:01:32 by rbenjami          #+#    #+#             */
/*   Updated: 2013/12/27 15:09:06 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	if (s && f)
	{
		i = 0;
		res = ft_memalloc(sizeof(char) * ft_strlen(s));
		while (s[i] != '\0')
		{
			res[i] = (*f)(i, s[i]);
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (0);
}
