#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>

const t_type	g_type_table[] = {
	{SECT_DATA, 'd'},
	{SECT_BSS, 'b'},
	{SECT_TEXT, 't'},
	{NULL, 's'}
};

void	ft_print_nlist_64(char *stringtable, struct nlist_64 *symbol,
		t_slice *list)
{
	char	type;

	if (!(symbol->n_type & N_STAB))
	{
		type = get_type_64(symbol, list);
		if (type != 'U' && type != 'u')
			ft_printf("%016llx ", symbol->n_value);
		else
			ft_putstr("                 ");
		ft_printf("%c ", type);
		ft_printf("%s\n", stringtable + symbol->n_un.n_strx);
	}
}

char	get_section_type_64(int n_sect, t_slice *sections)
{
	struct section_64	*section;
	int					i;

	i = 0;
	section = ft_slice_get(sections, n_sect - 1);
	while (g_type_table[i].sectname &&
			!ft_strequ(g_type_table[i].sectname, section->sectname))
		++i;
	return (g_type_table[i].symtype);
}

char	get_type_64(struct nlist_64 *sym, t_slice *sections)
{
	if (sym->n_type & N_EXT)
	{
		if ((sym->n_type & N_TYPE) == N_SECT)
			return (ft_toupper(get_section_type_64(sym->n_sect, sections)));
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return (sym->n_value ? 'C' : 'U');
		if ((sym->n_type & N_TYPE) == N_ABS)
			return ('A');
		if ((sym->n_type & N_TYPE) == N_INDR)
			return ('I');
		return (' ');
	}
	else
	{
		if ((sym->n_type & N_TYPE) == N_SECT)
			return (get_section_type_64(sym->n_sect, sections));
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return ('u');
		if ((sym->n_type & N_TYPE) == N_ABS)
			return ('a');
		if ((sym->n_type & N_TYPE) == N_INDR)
			return ('i');
		return (' ');
	}
}
