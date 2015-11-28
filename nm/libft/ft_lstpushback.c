/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/09/26 11:22:35 by jbalestr          #+#    #+#             */
/*   Updated: 2013/12/27 15:08:41 by espiroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

clude "libft.h"

void	ft_lstpushback(t_list **begin, t_list *new)
{
	t_list	*tmp;

	tmp = *begin;
	if (tmp == NULL)
		*begin = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
