#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <nm_otool.h>
#include <libft.h>


int			ft_otool_fat(char *ptr, char *name, int swap)
{
	struct fat_header		*h;
	struct fat_arch			*arch;
	uint32_t				offset;
	struct mach_header_64 	*header;
	size_t					i;

	h = (struct fat_header *)ptr;
	arch = (void *)h + sizeof(*h);
	offset = get_value(arch->offset, swap);
	i = 0;
	while ((int)i < get_value(h->nfat_arch, swap))
	{
		offset = get_value(arch->offset, swap);
		header = (void *)ptr + offset;
		if (get_value(arch->cputype, swap) == CPU_TYPE_X86_64)
			break;
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	header = (void *)ptr + offset;
	ft_otool((void *)header, name);
	return (0);
}

