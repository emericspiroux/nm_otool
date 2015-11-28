/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:14:36 by larry             #+#    #+#             */
/*   Updated: 2015/11/28 00:02:06 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
//offlist
void				add_tail_off(t_offlist *elem, t_offlist *to_add)
{
	to_add->prev = elem;
	elem->next = to_add;
}

t_offlist		*add_before_off(t_offlist *elem, t_offlist *to_add)
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

void			print_ar(uint32_t off, char *ptr, char *file)
{
	int				size;
	struct ar_hdr	*arch;
	char			*name;

	arch = (void*)ptr + off;
	name = catch_name(arch->ar_name);
	size = catch_size(arch->ar_name);
	ft_putchar('\n');
	ft_putstr(file);
	ft_putchar('(');
	ft_putstr(name);
	ft_putchar(')');
	ft_putstr(":\n");
	ft_nm((void*)arch + sizeof(*arch) + size, file);
}

void			browse_ar(t_offlist *lst, char *ptr, char *name)
{
	t_offlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		print_ar(tmp->off, ptr, name);
		tmp = tmp->next;
	}
}
//end offlist

//swap
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
//End sawp

//go
void	go_fat(char *ptr)
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
	ft_nm(ptr + swap_uint32(offset), NULL);
}

void	go_archive(char *ptr, char *name)
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
	browse_ar(lst, ptr, name);
}
//end go

//Sections
void				add_to_list(char *name, t_lsection *list)
{
	t_section	*add;

	if ((add = (t_section*)malloc(sizeof(t_section))) == NULL)
		return ;
	add->name = strdup(name);
	add->next = NULL;
	if (list->first == NULL)
	{
		list->first = add;
		list->last = add;
		add->nb = 1;
	}
	else
	{
		add->nb = list->last->nb + 1;
		list->last->next = add;
		list->last = add;
	}
}

void				add_seg(struct load_command *com, t_lsection *list)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)com;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		add_to_list(sec->sectname, list);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

t_lsection			*get_section(struct load_command *c, struct mach_header_64 *m)
{
	t_lsection			*list;
	unsigned int		i;

	i = 0;
	if ((list = (t_lsection*)malloc(sizeof(list))) == NULL)
		return (NULL);
	list->first = NULL;
	list->last = NULL;
	while (i < m->ncmds)
	{
		if (c->cmd == LC_SEGMENT_64)
			add_seg(c, list);
		c += c->cmdsize / sizeof(void *);
		i++;
	}
	return (list);
}
//End section

//Things
char				secto(t_lsection *sec, unsigned int n_sect)
{
	t_section	*tmp;

	tmp = sec->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!ft_strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
	return ('S');
}

char				typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr)
{
	char	ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(sec, n_sect);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

t_things			*add_before(t_things *yolo, t_things *to_add)
{
	t_things	*ret;

	ret = NULL;
	if (yolo->prev == NULL)
	{
		yolo->prev = to_add;
		to_add->next = yolo;
		ret = to_add;
	}
	else
	{
		to_add->next = yolo;
		to_add->prev = yolo->prev;
		yolo->prev->next = to_add;
		yolo->prev = to_add;
	}
	return (ret);
}

void				add_tail(t_things *yolo, t_things *to_add)
{
	to_add->prev = yolo;
	yolo->next = to_add;
}

t_things			*new_thing(struct nlist_64 list, char *strtable, t_lsection *sec)
{
	t_things	*tmp;

	tmp = (t_things*)malloc(sizeof(t_things));
	tmp->value = list.n_value;
	tmp->type = typing(list.n_type, list.n_sect, sec, list.n_value);
	tmp->str = ft_strdup(strtable + list.n_un.n_strx);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_things			*add_things(t_things *thing, struct nlist_64 list, char *strtable, t_lsection *sec)
{
	t_things	*bws_word;
	t_things	*tmp;
	t_things	*ret;

	tmp = new_thing(list, strtable, sec);
	if (thing == NULL)
		return (tmp);
	bws_word = thing;
	while (bws_word)
	{
		if (ft_strcmp(bws_word->str, tmp->str) > 0)
		{
			ret = add_before(bws_word, tmp);
			if (ret)
				thing = ret;
			break ;
		}
		else if (bws_word->next == NULL)
		{
			add_tail(bws_word, tmp);
			break ;
		}
		bws_word = bws_word->next;
	}
	return (thing);
}

void				print_nm(int value, char type, char *str)
{
	if (value == -1)
		ft_putstr("                ");
	else
		ft_putstr(ft_itohex(value, 16));
	ft_putstr(" ");
	ft_putchar(type);
	ft_putstr(" ");
	ft_putendl(str);
}

void				aff_things(t_things *thing)
{
	t_things	*tmp;

	tmp = thing;
	while (tmp)
	{
		if (tmp->value)
			print_nm(tmp->value, tmp->type, tmp->str);
		else if (ft_strcmp(&tmp->type, "U") == 0)
			print_nm(-1, tmp->type, tmp->str);
		else
			print_nm(0, tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

t_things			*del_things(t_things *thing)
{
	t_things	*tmp;
	t_things	*tmp2;

	tmp = thing;
	while (tmp)
	{
		if ((tmp->type == 'z' || tmp->type == 'Z') ||\
				(tmp->next && tmp->value && tmp->value == tmp->next->value))
		{
			if (tmp->type != 'z' && tmp->type != 'Z' && tmp->next->type == '?')
				tmp = tmp->next;
			tmp2 = tmp->next;
			if (tmp2)
				tmp2->prev = tmp->prev;
			tmp->prev->next = tmp2;
			free(tmp->str);
			free(tmp);
		}
		tmp = tmp->next;
	}
	return (thing);
}

//End things


void				end_nm(struct symtab_command *sym, char *ptr, t_lsection *sec)
{
	int					i;
	char				*strtable;
	struct nlist_64		*list;
	t_things			*thing;

	i = 0;
	list = (void *)ptr + sym->symoff;
	thing = NULL;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0
				&& strtable + list[i].n_un.n_strx && ft_strlen(strtable +\
					list[i].n_un.n_strx) && list[i].n_type != 100)
			thing = add_things(thing, list[i], strtable, sec);
		i++;
	}
	thing = del_things(thing);
	aff_things(thing);
}

void				find_oct(char *ptr)
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
	sec = get_section(command, header);
	while (i < cmd)
	{
		if (command->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)command;
			end_nm(sym, ptr, sec);
			break ;
		}
		command = (void *)command + command->cmdsize;
		i++;
	}
}

void				ft_nm(char *ptr, char *name)
{
	unsigned int		number;

	number = *(int *)ptr;
	if (number == MH_MAGIC_64)
		find_oct(ptr);
	else if (number == FAT_MAGIC || number == FAT_CIGAM)
		go_fat(ptr);
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		go_archive(ptr, name);
	else
		ft_putendl("Wrong binary format");
}

static int			errors(char *explain)
{
	ft_putstr("Error : ");
	ft_putendl(explain);
	return (-1);
}

int					main(int ac, char *av[])
{
	int fd;
	struct stat stat;
	char		*ptr;

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
		ft_nm(ptr, av[1]);
	if (fd != -1 && munmap(ptr, stat.st_size) < 0)
	{
		fd = errors("munmap file");
		return (1);
	}
	return (0);
}

