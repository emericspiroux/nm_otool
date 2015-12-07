/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_nm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 03:27:23 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:32:27 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static void				display_nm(int value, char type, char *str)
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

static void				aff_elem(t_memlist *elem)
{
	t_memlist	*tmp;

	tmp = elem;
	while (tmp)
	{
		if (tmp->value)
			display_nm(tmp->value, tmp->type, tmp->str);
		else if (ft_strcmp(&tmp->type, "U") == 0)
			display_nm(-1, tmp->type, tmp->str);
		else
			display_nm(0, tmp->type, tmp->str);
		tmp = tmp->next;
	}
}

static t_memlist		*del_elem(t_memlist *elem)
{
	t_memlist			*tmp;
	t_memlist			*tmp2;

	tmp = elem;
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
	return (elem);
}

void					end_nm(\
						struct symtab_command *sym, char *ptr, t_lsection *sec)
{
	int					i;
	char				*strtable;
	struct nlist_64		*list;
	t_memlist			*elem;

	i = 0;
	list = (void *)ptr + sym->symoff;
	elem = NULL;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0
				&& strtable + list[i].n_un.n_strx && ft_strlen(strtable +\
					list[i].n_un.n_strx) && list[i].n_type != 100)
			elem = add_elem(elem, list[i], strtable, sec);
		i++;
	}
	elem = del_elem(elem);
	aff_elem(elem);
}
