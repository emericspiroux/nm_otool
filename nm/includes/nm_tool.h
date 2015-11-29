/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:26:33 by larry             #+#    #+#             */
/*   Updated: 2015/11/28 01:57:37 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_TOOL_H
# define NM_TOOL_H
# include "libft.h"
# include <sys/mman.h>
# include <fcntl.h>
# include <ar.h>
# include <sys/stat.h>
# include <mach-o/ranlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <stdlib.h>
# include <unistd.h>

# define TXT "__TEXT"
# define TUT "__text"

typedef struct stat		t_stat;

typedef struct			s_things
{
	long int			value;
	char				type;
	char				*str;
	struct s_things		*next;
	struct s_things		*prev;
}						t_things;

typedef struct			s_section
{
	char				*name;
	unsigned int		nb;
	struct s_section	*next;
}						t_section;

typedef struct			s_lsection
{
	t_section			*first;
	t_section			*last;
}						t_lsection;

typedef struct			s_offlist
{
	uint32_t			off;
	uint32_t			strx;
	struct s_offlist	*next;
	struct s_offlist	*prev;
}						t_offlist;

void		ft_nm(char *ptr, char *name);
void		ft_otool(void *mem, char *file);

int			func_error();
t_things	*add_things(t_things *thing, struct nlist_64 list,\
			char *strtable, t_lsection *sec);

void		print_nm(int value, char type, char *str);
t_things	*del_things(t_things *thing);
t_lsection	*get_section(struct load_command *cmd, struct mach_header_64 *mo);
char		secto(t_lsection *sec, unsigned int n_sect);
t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx);

void		aff_things(t_things *thing);
void		browse_ar_nm(t_offlist *lst, char *ptr, char *name);
void		browse_ar_tool(t_offlist *lst, char *ptr, char *name);

int			catch_size(char *name);
char		*catch_name(char *name);
uint32_t	swap_uint32(uint32_t val);

void		go_fat(char *ptr);
void		go_archive(char *ptr, char *name);
char		typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr);

void		print_res(long unsigned int addr, unsigned int size, char *ptr);
void		check_64(struct load_command *com, struct mach_header_64 *mo);
t_offlist	*add_offt(t_offlist *lst, uint32_t off, uint32_t strx);
void		browse_cmd(struct load_command *com, struct mach_header_64 *mo);


#endif
