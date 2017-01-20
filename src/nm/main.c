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

static int	ft_error(char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", msg);
	return (EXIT_FAILURE);
}

int			ft_openfile(int fd, char *name, char *errname)
{
	char			*ptr;
	struct stat		buf;

	if (fstat(fd, &buf) < 0)
		return (ft_error(ft_strerror()));
	if (buf.st_size == 0)
		return (ft_error("The file is not a valid binary (empty file)"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (ft_error("Unable to map file to memory"));
	ft_nm(ptr, name, errname);
	if (munmap(ptr, buf.st_size) < 0)
		return (ft_error("Unable to unmap file"));
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
		if ((fd = open("a.out", O_RDONLY)) != -1 &&
				ft_openfile(fd, "a.out", "a.out") == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		ft_printf("Usage %s <files>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	while (++i < argc)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			return (ft_error(ft_strerror()));
		if ((fd = ft_openfile(fd, argc > 2 ? argv[i] : NULL, argv[i])))
			return (fd);
	}
	return (EXIT_SUCCESS);
}
