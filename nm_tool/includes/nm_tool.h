/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_tool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 14:26:33 by larry             #+#    #+#             */
/*   Updated: 2015/11/30 03:28:36 by larry            ###   ########.fr       */
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
# include "struct.h"
# define TXT "__TEXT"
# define TUT "__text"


/*
** NM
*/
void		doNm(char *ptr, char *name);
void		doFat(char *ptr);
void		doArchive(char *ptr, char *name);
void		browse_ar_nm(t_offlist *lst, char *ptr, char *name);
char		typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr);
t_lsection	*getSection(struct load_command *cmd, struct mach_header_64 *mo);
t_memList	*addElem(t_memList *e, struct nlist_64 l, char *s, t_lsection *sec);
void		endNm(struct symtab_command *sym, char *ptr, t_lsection *sec);

/*
** TOOL
*/
void		doOtool(void *mem, char *name);
void		doFatTool(char *ptr);
void		doArchiveTool(void *ptr, char *name);
void		browse_ar_tool(t_offlist *lst, char *ptr, char *name);


/*
** common
*/
int			catch_size(char *name);
char		*catch_name(char *name);
uint32_t	swap_uint32(uint32_t val);
void		displayRes(long unsigned int addr, unsigned int size, char *ptr);
void		browse_cmd(struct load_command *com, struct mach_header_64 *mo);
t_offlist	*add_off(t_offlist *lst, uint32_t off, uint32_t strx);


#endif
