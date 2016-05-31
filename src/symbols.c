#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>

/*
** TODO: type des symboles, ne pas afficher l'addresse des undefine
*/
void	ft_print_nlist64(char *stringtable, struct nlist_64 *symbol)
{
	if (!(symbol->n_type & N_STAB))
	{
		ft_printf("%016llx ", symbol->n_value);
		ft_printf("%hhx ", symbol->n_type);
		ft_printf("%c ", get_type(symbol));
		ft_printf("%d ", symbol->n_sect);
		ft_printf("%s\n", stringtable + symbol->n_un.n_strx);
	}
}
