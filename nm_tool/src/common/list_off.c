/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_off.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 01:30:36 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:32:59 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

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

static t_offlist		*new_elem_offlist(uint32_t off, uint32_t strx)
{
	t_offlist			*tmp;

	tmp = (t_offlist*)malloc(sizeof(t_offlist));
	tmp->off = off;
	tmp->strx = strx;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_offlist				*add_off(t_offlist *lst, uint32_t off, uint32_t strx)
{
	t_offlist			*tmp;
	t_offlist			*tmp2;
	t_offlist			*ret;

	tmp = new_elem_offlist(off, strx);
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
