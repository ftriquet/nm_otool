/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:50:38 by akpenou           #+#    #+#             */
/*   Updated: 2017/01/20 17:42:27 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libft.h>
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
#include <mach-o/fat.h>

int			ft_otool_dylib(char *ptr, t_slice *list, char *name)
{
	if (name)
		ft_printf("\n%s:\n", name);
	(void)ptr;
	(void)list;
	return (0);
}


void		ft_otool(char *ptr, char *name)
{
	unsigned int	magic_number;
	t_slice				*list;

	magic_number = *(int *)ptr;
	list = ft_new_slice(15);
	if (magic_number == MH_MAGIC_64)
		handler_64(ptr, name);
	else if (magic_number == MH_MAGIC)
		handler_32(ptr, name);
	else if (magic_number == MH_DYLIB)
		ft_otool_dylib(ptr, list, name);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		ft_otool_fat(ptr, name, (magic_number == FAT_CIGAM));
	else
		ft_dprintf(STDERR_FILENO, "The file is not a valid binary\n");
}

int			ft_openfile(int fd, char *name)
{
	char			*ptr;
	struct stat		buf;

	if (fstat(fd, &buf) < 0)
		return ft_error(ft_strerror());
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error("Unable to map file."));
	ft_otool(ptr, name);
	if (munmap(ptr, buf.st_size) < 0)
		return (ft_error("Unable to unmap file."));
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
		printf("Usage %s <files>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	while (++i < argc)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return (ft_error(ft_strerror()));
		if ((fd = ft_openfile(fd, argv[i])))
			return (fd);
	}
	return (EXIT_SUCCESS);
}
