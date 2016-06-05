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

int			ft_openfile(int fd)
{
	char			*ptr;
	struct stat		buf;

	if (fstat(fd, &buf) < 0 || (ptr = mmap(0, buf.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("system failed");
		return (EXIT_FAILURE);
	}
	ft_nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_printf("munmap failed");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
	int				fd;
	int				i;

	fd = 0;
	i = 0;
	if (argc == 1)
	{
		if ((fd = open("a.out", O_RDONLY)) != -1 && ft_openfile(fd) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		ft_printf("Usage %s <files>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	while (++i < argc)
	{
		if (argc > 2)
			ft_printf("%s:\n", argv[i]);
		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_putendl("open failed");
			return (EXIT_FAILURE);
		}
		if ((fd = ft_openfile(fd)))
			return (fd);
	}
	return (EXIT_SUCCESS);
}
