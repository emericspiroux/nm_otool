/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_archive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 02:34:18 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 02:36:11 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

void				do_archive(char *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	t_doarchive		var;

	var.i = 0;
	arch = (void*)ptr + SARMAG;
	var.size2 = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + var.size2;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + var.size2 + 4;
	var.size = *((int *)test);
	lst = NULL;
	var.size = var.size / sizeof(struct ranlib);
	while (var.i < var.size)
	{
		lst = add_off(lst, ran[var.i].ran_off, ran[var.i].ran_un.ran_strx);
		var.i++;
	}
	browse_ar_nm(lst, ptr, name);
}
