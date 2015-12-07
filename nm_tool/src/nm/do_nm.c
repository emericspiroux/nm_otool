/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 03:29:26 by larry             #+#    #+#             */
/*   Updated: 2015/12/07 17:58:27 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static void					find_oct(char *ptr)
{
	t_doarchive				var;
	struct mach_header_64	*header;
	struct load_command		*command;
	struct symtab_command	*sym;
	t_lsection				*sec;

	var.i = 0;
	header = (struct mach_header_64 *)ptr;
	var.cmd = header->ncmds;
	command = (void *)ptr + sizeof(*header);
	sec = get_section(command, header);
	while (var.i < var.cmd)
	{
		if (command->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)command;
			end_nm(sym, ptr, sec);
			break ;
		}
		command = (void *)command + command->cmdsize;
		var.i++;
	}
}

void						do_nm(char *ptr, char *name)
{
	unsigned int			number;

	number = *(int *)ptr;
	if (number == MH_MAGIC_64)
		find_oct(ptr);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		do_fat(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		do_archive(ptr, name);
	else
		ft_putendl("Wrong binary format");
}
