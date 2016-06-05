#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

int		ft_display_symlist_64(struct mach_header_64 *header, t_slice *sectlist)
{
	struct load_command		*lc;
	size_t					i;
	struct symtab_command	*symtab;
	t_slice					*symlist;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;
			symlist = ft_build_symlist_64(header, symtab->nsyms, symtab->symoff);
			ft_slice_merge_sort(symlist, &alpha_cmp, (void *)header + symtab->stroff);
			ft_print_symlist_64(symlist, sectlist, (void *)header + symtab->stroff);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	return (1);
}

int		ft_display_symlist_32(struct mach_header *header, t_slice *sectlist)
{
	struct load_command		*lc;
	size_t					i;
	struct symtab_command	*symtab;
	t_slice					*symlist;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;
			symlist = ft_build_symlist_32(header, symtab->nsyms, symtab->symoff);
			ft_slice_merge_sort(symlist, &alpha_cmp, (void *)header + symtab->stroff);
			ft_print_symlist_32(symlist, sectlist, (void *)header + symtab->stroff);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
	return (1);
}
