#ifndef NM_OTOOL_H
# define NM_OTOOL_H
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <libft.h>

typedef struct s_type
{
	char		*sectname;
	char		symtype;
}				t_type;

extern t_type	g_type_table[];
/*
 ** section.c
 */
void			ft_build_section_list_64(t_slice *list, struct mach_header_64 *header);

void			ft_add_segment_to_list_64(struct segment_command_64 *segment,
		t_slice *list);
void			ft_build_section_list_32(t_slice *list, struct mach_header *header);
void			ft_add_segment_to_list_32(struct segment_command *segment,
		t_slice *list);
/*
 ** nm.c
 */
int				ft_display_symtab_64(struct mach_header_64 *header, int nsyms,
		int symoff, int stroff, t_slice *list);
int				ft_display_symlist_64(struct mach_header_64 *header, t_slice *list);
int				ft_display_symlist_32(struct mach_header *header, t_slice *list);
int				ft_display_symtab_32(struct mach_header *header, int nsyms,
		int symoff, int stroff, t_slice *list);

/*
 ** main.c
 */
void			print_section(void *section);

void			nm(char *ptr);

/*
 ** symbols.c
 */
void			ft_print_nlist_64(char *stringtable, struct nlist_64 *symbol, t_slice *list);
char			get_type_64(struct nlist_64 *sym, t_slice *sections);
char			get_section_type_64(int n_sect, t_slice *sections);

void			ft_print_nlist_32(char *stringtable, struct nlist *symbol, t_slice *list);
char			get_type_32(struct nlist *sym, t_slice *sections);
char			get_section_type_32(int n_sect, t_slice *sections);

/*
 ** dump_header.c
 */
int				dump_header_64(struct mach_header_64 *header);
int				dump_header(void *header_ptr);

#endif
