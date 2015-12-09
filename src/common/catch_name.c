/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 01:41:31 by larry             #+#    #+#             */
/*   Updated: 2015/11/28 01:41:50 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

char		*catch_name(char *name)
{
	int		length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}
