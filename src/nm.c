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

int			ft_nm(char *ptr)
{
	int		magic_number;
	t_slice	*list;

	magic_number = *(int *)ptr;
	list = ft_new_slice(15);
	if (magic_number == MH_MAGIC_64)
		return (ft_nm_64(ptr, list));
	if (magic_number == MH_MAGIC)
		return (ft_nm_32(ptr, list));
	if (magic_number === MH_DYLIB)
		return (ft_nm_dylib(ptr, list));
}
