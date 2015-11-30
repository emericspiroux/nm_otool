/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_ar_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 01:36:10 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 02:54:44 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static void			print_ar_tool(uint32_t off, char *ptr, char *file)
{
	int				size;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size = catch_size(arch->ar_name);
	ft_putchar('\n');
	ft_putstr(file);
	ft_putchar('(');
	ft_putstr(name);
	ft_putchar(')');
	ft_putstr(":\n");
	doOtool((void*)arch + sizeof(*arch) + size, file);
}

void				browse_ar_tool(t_offlist *lst, char *ptr, char *name)
{
	t_offlist		*tmp;

	tmp = lst;
	while (tmp)
	{
		print_ar_tool(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}
