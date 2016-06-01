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
/*
** section.c
*/
void		ft_build_section_list(t_slice *list, struct mach_header_64 *header);

void		ft_add_segment_to_list(struct segment_command_64 *segment,
		t_slice *list);
/*
** nm.c
*/
int		ft_display_symtab(struct mach_header_64 *header, int nsyms,
		int symoff, int stroff, t_slice *list);
int		ft_display_symlist_64(struct mach_header_64 *header, t_slice *list);

/*
** main.c
*/
void	print_section(void *section);

void	nm(char *ptr);

/*
** symbols.c
*/
void	ft_print_nlist64(char *stringtable, struct nlist_64 *symbol, t_slice *list);
char	get_type(struct nlist_64 *sym, t_slice *sections);
char	get_section_type(int n_sect, t_slice *sections);

/*
** dump_header.c
*/
int		dump_header_64(struct mach_header_64 *header);

int	dump_header(void *header_ptr);

#endif
