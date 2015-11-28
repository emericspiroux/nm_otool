/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 20:44:57 by larry             #+#    #+#             */
/*   Updated: 2015/11/28 01:31:07 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

//fat
void		go_fati(char *ptr)
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
	ft_otool(ptr + swap_uint32(offset), NULL);
}

void		go_archivi(void *ptr, char *name)
{
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	t_offlist		*lst;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size_fuck = catch_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size_fuck + 4;
	size = *((int *)test);
	lst = NULL;
	size = size / sizeof(struct ranlib);
	while (i < size)
	{
		lst = add_offt(lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	browse_art(lst, ptr, name);
}

void		ft_otool(void *mem, char *name)
{
	struct mach_header_64		*mo;
	struct load_command			*com;
	unsigned int				number;

	mo = mem;
	com = mem + sizeof(struct mach_header_64);
	number = *(int *)mem;
	if (number == MH_MAGIC_64)
		browse_cmd(com, mo);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		go_fati(mem);
	else if (!ft_strncmp(mem, ARMAG, SARMAG))
		go_archivi(mem, name);
	else
		ft_putendl("Wrong binary format");
}


//offlist
static void				add_tail_off(t_offlist *elem, t_offlist *to_add)
{
	to_add->prev = elem;
	elem->next = to_add;
}

static t_offlist		*add_before_off(t_offlist *elem, t_offlist *to_add)
{
	t_offlist	*ret;

	ret = NULL;
	if (elem->prev == NULL)
	{
		elem->prev = to_add;
		to_add->next = elem;
		ret = to_add;
	}
	else
	{
		to_add->next = elem;
		to_add->prev = elem->prev;
		elem->prev->next = to_add;
		elem->prev = to_add;
	}
	return (ret);
}

t_offlist		*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist	*tmp;
	t_offlist	*tmp2;
	t_offlist	*ret;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	tmp->prev = NULL;
	if (!lst)
		return (tmp);
	tmp2 = lst;
	while (tmp2)
	{
		if (tmp2->off > tmp->off)
		{
			ret = add_before_off(tmp2, tmp);
			if (ret)
				lst = ret;
			break ;
		}
		else if (tmp2->next == NULL)
		{
			add_tail_off(tmp2, tmp);
			break ;
		}
		tmp2 = tmp2->next;
	}
	return (lst);
}

void			print_art(uint32_t off, char *ptr, char *file)
{
	int				size;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size = catch_size(arch->ar_name);
	ft_putstr(file);
	ft_putchar('(');
	ft_putstr(name);
	ft_putstr("):\n");
	ft_otool((void*)arch + sizeof(*arch) + size, file);
}

void			browse_art(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_art(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}


//catch
uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

int			catch_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

char		*catch_name(char *name)
{
	int		length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}

//ot_print
static char		read_tab(int i)
{
	char	*tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

static char		*ft_itoa_base(int val, int base, int output_size)
{
	char			buffer[output_size + 1];
	char			*p;
	unsigned int	unsigned_val;

	unsigned_val = (unsigned int)val;
	if (base > 36 || base < 2)
		return (NULL);
	buffer[output_size] = 0;
	p = buffer + output_size - 1;
	*p = '0';
	if (unsigned_val > 0)
	{
		while (unsigned_val > 0)
		{
			*p-- = read_tab(unsigned_val % base);
			unsigned_val = unsigned_val / base;
			if (p < buffer)
				break ;
		}
		p++;
	}
	while (p > buffer)
		*--p = '0';
	return (ft_strdup(p));
}

void			print_res(long unsigned int addr, unsigned int size, char *ptr)
{
	unsigned int	i;
	char			*str;

	i = 0;
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_putstr(ft_itohex(addr, 16));
			ft_putstr(" ");
		}
		str = ft_itoa_base(ptr[i], 16, 2);
		ft_putstr(str);
		ft_putstr(" ");
		free(str);
		if ((i + 1) % 16 == 0)
			write(1, "\n", 1);
		i++;
	}
	if (!(i % 16 == 0))
		write(1, "\n", 1);
}


//check
void	check_text(struct segment_command_64 *seg, struct mach_header_64 *mo)
{
	struct section_64	*sec;
	unsigned int		i;

	i = 0;
	sec = (struct section_64*)\
					(seg + sizeof(struct segment_command_64*) / sizeof(void*));
	while (i < seg->nsects)
	{
		if (!ft_strcmp(sec->sectname, TUT) && !ft_strcmp(sec->segname, TXT))
		{
			write(1, "(__TEXT,__text) section\n", 24);
			print_res(sec->addr, sec->size, (char *)mo + sec->offset);
		}
		sec = (struct section_64*)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void	check_64(struct load_command *com, struct mach_header_64 *mo)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)com;
	check_text(seg, mo);
}




//ft_tools
static int		errors(void)
{
	ft_putendl_fd("Error", 2);
	return (-1);
}

void			browse_cmd(struct load_command *com, struct mach_header_64 *mo)
{
	unsigned int		i;

	i = 0;
	while (i < mo->ncmds)
	{
		if (com->cmd == LC_SEGMENT_64)
			check_64(com, mo);
		com += com->cmdsize / sizeof(void *);
		i++;
	}
}

static int		if_forest(int i, char **av)
{
	t_stat		stat;
	void		*mem;
	int			fd;

	if ((fd = open(av[i], O_RDONLY)) == -1)
		fd = errors();
	if (fd != -1 && (fstat(fd, &stat) == -1))
		fd = errors();
	if (fd != -1 &&
			!(mem = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
		fd = errors();
	if (fd != -1)
		ft_otool(mem, av[i]);
	if (fd != -1 && munmap(mem, stat.st_size) < 0)
	{
		fd = errors();
		return (0);
	}
	return (1);
}

int				main(int ac, char **av)
{
	int		i;

	if (ac < 2)
		ft_putstr("bad argument\n");
	i = 1;
	while (i < ac)
	{
		ft_putstr("Archive : ");
		ft_putstr(av[i]);
		ft_putstr("\n");
		if (!if_forest(i, av))
			break ;
		i++;
	}
	return (0);
}
