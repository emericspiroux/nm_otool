/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doNm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 03:29:26 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:29:32 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static void						findOct(char *ptr)
{
	int						cmd;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*command;
	struct symtab_command	*sym;
	t_lsection				*sec;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	cmd = header->ncmds;
	command = (void *)ptr + sizeof(*header);
	sec = getSection(command, header);
	while (i < cmd)
	{
		if (command->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)command;
			endNm(sym, ptr, sec);
			break ;
		}
		command = (void *)command + command->cmdsize;
		i++;
	}
}

void						doNm(char *ptr, char *name)
{
	unsigned int			number;

	number = *(int *)ptr;
	if (number == MH_MAGIC_64)
		findOct(ptr);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		doFat(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		doArchive(ptr, name);
	else
		ft_putendl("Wrong binary format");
}
