/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 03:01:26 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:07:38 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static t_memlist			*add_before(t_memlist *lst, t_memlist *to_add)
{
	t_memlist				*ret;

	ret = NULL;
	if (lst->prev == NULL)
	{
		lst->prev = to_add;
		to_add->next = lst;
		ret = to_add;
	}
	else
	{
		to_add->next = lst;
		to_add->prev = lst->prev;
		lst->prev->next = to_add;
		lst->prev = to_add;
	}
	return (ret);
}

static void					add_tail(t_memlist *yolo, t_memlist *to_add)
{
	to_add->prev = yolo;
	yolo->next = to_add;
}

static t_memlist			*new_elem(\
	struct nlist_64 list, char *strtable, t_lsection *sec)
{
	t_memlist				*tmp;

	tmp = (t_memlist*)malloc(sizeof(t_memlist));
	tmp->value = list.n_value;
	tmp->type = typing(list.n_type, list.n_sect, sec, list.n_value);
	tmp->str = ft_strdup(strtable + list.n_un.n_strx);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_memlist					*add_elem(\
	t_memlist *elem, struct nlist_64 list, char *strtable, t_lsection *sec)
{
	t_memlist				*bws_word;
	t_memlist				*tmp;
	t_memlist				*ret;

	tmp = new_elem(list, strtable, sec);
	if (elem == NULL)
		return (tmp);
	bws_word = elem;
	while (bws_word)
	{
		if (ft_strcmp(bws_word->str, tmp->str) > 0)
		{
			ret = add_before(bws_word, tmp);
			if (ret)
				elem = ret;
			break ;
		}
		else if (bws_word->next == NULL)
		{
			add_tail(bws_word, tmp);
			break ;
		}
		bws_word = bws_word->next;
	}
	return (elem);
}
