/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 18:28:43 by espiroux          #+#    #+#             */
/*   Updated: 2015/12/07 18:29:58 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static int			errors(void)
{
	ft_putstr("Error\n");
	return (-1);
}

static int			open_memory(int ac, int i, char **av)
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
		do_nm(ptr, av[i]);
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
		if (!open_memory(ac, i, av))
			break ;
		i++;
	}
	return (0);
}
