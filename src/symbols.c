#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>


const t_type	g_type_table[] = {
	{"__data", 'd'},
	{"__bss", 'b'},
	{"__text", 't'},
	{NULL, 's'}
};

/*
** TODO: type des symboles, ne pas afficher l'addresse des undefine
*/
void	ft_print_nlist64(char *stringtable, struct nlist_64 *symbol,
		t_slice *list)
{
	if (!(symbol->n_type & N_STAB))
	{
		if (symbol->n_value)
			ft_printf("%016llx ", symbol->n_value);
		else
			ft_putstr("                 ");
		// ft_printf("%hhx ", symbol->n_type);
		ft_printf("%c ", get_type(symbol, list));
		// ft_printf("%d ", symbol->n_sect);
		ft_printf("%s\n", stringtable + symbol->n_un.n_strx);
	}
}

char	get_section_type(int n_sect, t_slice *sections)
{
	struct section_64	*section;
	int					i;

	i = 0;
	section = ft_slice_get(sections, n_sect - 1);
	while (g_type_table[i].sectname &&
			!ft_strequ(g_type_table[i].sectname, section->sectname))
		++i;
	return g_type_table[i].symtype;
}

//  	__common	__DATA 	: 	globales non initialisees => S
//  	__data		__DATA 	: 	globales initialisees => D
//  	__bss		__DATA 	: 	variables static
char	get_type(struct nlist_64 *sym, t_slice *sections)
{
	if (sym->n_type & N_EXT)
	{
		// upeercase
		if ((sym->n_type & N_TYPE) == N_SECT)
			return (ft_toupper(get_section_type(sym->n_sect, sections)));
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return 'U';
		if ((sym->n_type & N_TYPE) == N_ABS)
			return 'A';
		if ((sym->n_type & N_TYPE) == N_PBUD)
			return 'P';
		if ((sym->n_type & N_TYPE) == N_INDR)
			return 'I';
		return 'N';
	}
	else
	{
		// lowercase
		if ((sym->n_type & N_TYPE) == N_SECT)
			return (get_section_type(sym->n_sect, sections));
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return 'u';
		if ((sym->n_type & N_TYPE) == N_ABS)
			return 'a';
		if ((sym->n_type & N_TYPE) == N_PBUD)
			return 'p';
		if ((sym->n_type & N_TYPE) == N_INDR)
			return 'i';
		return 'n';
	}
}

