/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 03:25:35 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:31:51 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_tool.h"

static void						add_list(char *name, t_lsection *list)
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

static void						add_segment(\
									struct load_command *com, t_lsection *list)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)com;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		add_list(sec->sectname, list);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

t_lsection						*get_section(\
							struct load_command *c, struct mach_header_64 *m)
{
	t_lsection					*list;
	unsigned int				i;

	i = 0;
	if ((list = (t_lsection*)malloc(sizeof(list))) == NULL)
		return (NULL);
	list->first = NULL;
	list->last = NULL;
	while (i < m->ncmds)
	{
		if (c->cmd == LC_SEGMENT_64)
			add_segment(c, list);
		c += c->cmdsize / sizeof(void *);
		i++;
	}
	return (list);
}
