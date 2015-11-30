/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 12:21:39 by rbenjami          #+#    #+#             */
/*   Updated: 2015/11/27 21:48:01 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
static char *	init_string(int len)
{
	int			i;
	char		*str;

	i = 0;
	str = (char *) malloc((sizeof(char) * len) + 1);
	while (i < len)
	{
		str[i] = '0';
		i++;
	}
	str[len] = '\0';
	return (str);
}

char*			ft_itohex(int n, int nb_z)
{
	char		*convert;
	int			res;
	int			i;
	char		tab[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

	i = 0;
	convert = init_string(nb_z);
	if (n < 0 || nb_z <= 0)
		return (convert);

	while (n > 0)
	{
		res = n % 16;
		convert[((nb_z - 1) - i)] = tab[res];
		n /= 16;
		i++;
	}
	return (convert);
}
