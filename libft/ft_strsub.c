/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:01:32 by rbenjami          #+#    #+#             */
/*   Updated: 2013/12/27 15:09:13 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	tmp = (char *)malloc((len + 1) * sizeof(char));
	ft_strncpy(tmp, s + start, len);
	tmp[len] = '\0';
	return (tmp);
}
