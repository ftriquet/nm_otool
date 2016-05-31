#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

int		ft_display_symtab(struct mach_header_64 *header, int nsyms,
		int symoff, int stroff)
{
	int				i;
	struct nlist_64	*symbol;
	char			*string_table;

	i = 0;
	symbol = (void *)header + symoff;
	string_table = (void *header) + stroff;
	while (i < nsyms)
	{
		ft_print_nlist64(symbol + i);
		++i;
	}
	return (1);
}


int		ft_display_symlist_64(struct mach_header_64 *header)
{
	struct load_command		*lc;
	int						i;
	struct symtab_command	*symtab;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;
			ft_display_symtab(header, symtab->nsyms,
					symtab->symoff, symtab->stroff);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	return (1);
}
