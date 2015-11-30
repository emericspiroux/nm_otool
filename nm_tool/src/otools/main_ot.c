/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 20:44:57 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 02:54:18 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static int						errors(void)
{
	ft_putendl_fd("Error", 2);
	return (-1);
}

static int						openMemory(int i, char **av)
{
	t_stat						stat;
	void						*mem;
	int							fd;

	if ((fd = open(av[i], O_RDONLY)) == -1)
		fd = errors();
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors();
	if (fd != -1 &&
			!(mem = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors();
	if (fd != -1)
		doOtool(mem, av[i]);
	if (fd != -1 && munmap(mem, stat.st_size) < 0)
	{
		fd = errors();
		return (0);
	}
	return (1);
}

int								main(int ac, char **av)
{
	int							i;

	if (ac < 2)
		ft_putstr("bad argument\n");
	i = 1;
	while (i < ac)
	{
		ft_putstr("Archive : ");
		ft_putstr(av[i]);
		ft_putstr("\n");
		if (!openMemory(i, av))
			break ;
		i++;
	}
	return (0);
}
