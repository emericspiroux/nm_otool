/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doArchive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 02:34:18 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 02:36:11 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

void				doArchive(char *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				size2;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size2 = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size2;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size2 + 4;
	size = *((int *)test);
	lst = NULL;
	size = size / sizeof(struct ranlib);
	while (i < size)
	{
		lst = add_off(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_ar_nm(lst, ptr, name);
}
