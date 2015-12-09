/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 02:46:20 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:33:24 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static char				read_tab(int i)
{
	char				*tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

static char				*ft_itoa_base(int val, int base, int output_size)
{
	char				buffer[output_size + 1];
	char				*p;
	unsigned int		unsigned_val;

	unsigned_val = (unsigned int)val;
	if (base > 36 || base < 2)
		return (NULL);
	buffer[output_size] = 0;
	p = buffer + output_size - 1;
	*p = '0';
	if (unsigned_val > 0)
	{
		while (unsigned_val > 0)
		{
			*p-- = read_tab(unsigned_val % base);
			unsigned_val = unsigned_val / base;
			if (p < buffer)
				break ;
		}
		p++;
	}
	while (p > buffer)
		*--p = '0';
	return (ft_strdup(p));
}

void					display_res(\
						long unsigned int addr, unsigned int size, char *ptr)
{
	unsigned int		i;
	char				*str;

	i = 0;
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_putstr(ft_itohex(addr, 16));
			ft_putstr(" ");
		}
		str = ft_itoa_base(ptr[i], 16, 2);
		ft_putstr(str);
		ft_putstr(" ");
		free(str);
		if ((i + 1) % 16 == 0)
			write(1, "\n", 1);
		i++;
	}
	if (!(i % 16 == 0))
		write(1, "\n", 1);
}
