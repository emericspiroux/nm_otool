/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:14:36 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 04:06:53 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static int			errors()
{
	ft_putstr("Error\n");
	return (-1);
}

static int			openMemory(int ac, int i, char **av)
{
	t_stat			stat;
	char			*ptr;
	int				fd;

	if (ac > 2)
	{
		ft_putstr("\n");
		ft_putstr(av[i]);
		ft_putstr(":\n");
	}
	if ((fd = open(av[i], O_RDONLY)) == -1)
		fd = errors();
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors();
	if (fd != -1 &&
			!(ptr = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors();
	if (fd != -1)
		doNm(ptr, av[i]);
	if (fd != -1 && munmap(ptr, stat.st_size) < 0)
	{
		fd = errors();
		return (0);
	}
	return (1);
}

int					main(int ac, char *av[])
{
	int				i;

	if (ac < 2)
	{
		av[1] = ft_strdup("a.out");
		ac = 2;
	}
	i = 1;
	while (i < ac)
	{
		if (!openMemory(ac, i, av))
			break ;
		i++;
	}
	return (0);
}

