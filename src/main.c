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

char	*g_strrrrrrrrrrrrrrrrrrrrrrrrrr = "LOL";
char	*g_loooooooooooooooooooooooool;

void	print_section(void *section)
{
	struct section_64 *sec;

	sec = (struct section_64 *)section;
	ft_putendl("================");
	ft_printf("%s\n", sec->sectname);
	ft_printf("%s\n", sec->segname);
	ft_putendl("================");
}

void	nm(char *ptr)
{
	int		magic_number;
	t_slice	*list;

	magic_number = *((int *)ptr);
	if (magic_number == MH_MAGIC_64)
	{
		list = ft_new_slice(15);
		ft_build_section_list_64(list, ptr);
		ft_display_symlist_64(ptr, list);
	}
}

static int TEST_STATIC(void) {
	static int TEST_STATIC_VAR;
	static int TEST_STATIC_VAR_INIT = 0;
	ft_putendl("adasd");
}
int main(int ac, char **av)
{
	struct stat	buf;
	int			fd;
	char		*ptr;
	// TEST_STATIC();
	if (ac != 2)
	{
		puts("Need arg");
		exit(1);
	}
	fd = open (av[1], O_RDONLY);
	if (fd == -1)
	{
		puts("Error open");
		exit(1);
	}
	if (fstat(fd, &buf) < 0)
	{
		puts("Error stat");
		exit(1);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		puts("Error mmap");
		exit(1);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		puts("Error munmap");
		exit(1);
	}
}
