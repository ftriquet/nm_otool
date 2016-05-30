#include <mach-o/loader.h>
#include <libft.h>
#include <mach-o/nlist.h>

/*
** otool -h
*/
int		dump_header_64(struct mach_header_64 *header)
{
	ft_printf("%10x %10u %10u %10x %10u %10u %10u %10x\n",
			header->magic,
			header->cputype,
			header->cpusubtype,
			header->filetype,
			header->ncmds,
			header->sizeofcmds,
			header->flags);
	return (1);
}

int	dump_header(void *header_ptr)
{
	int		magic_number;

	magic_number = *(int *)header_ptr;
	ft_putendl("Mach header");
	ft_printf("%10s %10s %10s %10s %10s %10s %10s %10s\n",
			"magic", "cputype", "cpusubtype", "caps", "filetype", "ncmds",
			"sizeofcmds", "flags");
	if (magic_number == MH_MAGIC_64)
		return (dump_header_64((struct mach_header_64 *)header_ptr));
}

