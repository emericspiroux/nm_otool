/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fat_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 02:54:00 by espiroux          #+#    #+#             */
/*   Updated: 2015/12/07 18:00:15 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

void					do_fat_tool(char *ptr)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			x;
	uint32_t			offset;

	fat = (void*)ptr;
	x = fat->nfat_arch;
	x = swap_uint32(x);
	arch = (void*)ptr + sizeof(fat);
	while (x)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void*);
		x--;
	}
	do_otool(ptr + swap_uint32(offset), NULL);
}
