/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:13:56 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:33:52 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

 typedef struct stat		t_stat;

 typedef struct				s_memList
 {
 	long int				value;
 	char					type;
 	char					*str;
 	struct s_memList			*next;
 	struct s_memList			*prev;
 }							t_memList;

 typedef struct				s_section
 {
 	char					*name;
 	unsigned int			nb;
 	struct s_section		*next;
 }							t_section;

 typedef struct				s_lsection
 {
 	t_section				*first;
 	t_section				*last;
 }							t_lsection;

 typedef struct				s_offlist
 {
 	uint32_t				off;
 	uint32_t				strx;
 	struct s_offlist		*next;
 	struct s_offlist		*prev;
 }							t_offlist;

#endif
