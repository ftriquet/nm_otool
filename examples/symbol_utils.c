#include <mach-o/nlist.h>

int			ft_is_debug_sym(struct nlist_64 *sym)
{
	return (sym->n_type & N_STAB);
}
