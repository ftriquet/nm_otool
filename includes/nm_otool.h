#ifndef NM_OTOOL_H
# define NM_OTOOL_H
# include <libft.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

/*
** section.c
*/
void		ft_build_section_list(t_list *list, struct mach_header_64 *header);
void		ft_add_segment_to_list(struct segment_command_64 *segment,
		t_list *list);


/*
** symbol_utils.c
*/
int			ft_is_debug_sym(struct nlist_64 *sym);


/*
** nm.c
*/
int			ft_display_symlist_64(struct mach_header_64 *header);
int			ft_display_symtab(struct mach_header_64 *header, int nsyms,
		int symoff, int stroff);

/*
** symbols.c
*/
void		ft_print_nlist64(char *stringtable, struct nlist_64 *symbol);
#endif
