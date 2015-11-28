/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:50:44 by rbenjami          #+#    #+#             */
/*   Updated: 2014/01/07 03:39:52 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\t') || (c == '\n' || c == '\v')
		|| (c == '\f' || c == '\r') ||c == '\12');
}

char		*ft_strtrim(char const *s)
{
	int		len;

	if (!s)
		return (NULL);
	while (*s && ft_isspace(*s))
		s++;
	len = ft_strlen(s) - 1;
	while (len > 0 && s[len] && ft_isspace(s[len]))
		len--;
	return (ft_strsub(s, 0, len + 1));
}
