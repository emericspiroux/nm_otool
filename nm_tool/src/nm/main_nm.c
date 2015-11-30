/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:14:36 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:31:18 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static int			errors(char *explain)
{
	ft_putstr("Error : ");
	ft_putendl(explain);
	return (-1);
}

int					main(int ac, char *av[])
{
	int				fd;
	struct stat		stat;
	char			*ptr;

   	if (ac > 2)
   	{
   		ft_putstr("\n");
   		ft_putstr(av[1]);
   		ft_putendl(":");
   	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		fd = errors("open file");
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors("stat file");
	if (fd != -1 &&
			!(ptr = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors("mmap file");
	if (fd != -1)
		doNm(ptr, av[1]);
	if (fd != -1 && munmap(ptr, stat.st_size) < 0)
	{
		fd = errors("munmap file");
		return (1);
	}
	return (0);
}

