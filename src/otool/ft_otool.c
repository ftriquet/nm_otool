/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:50:38 by akpenou           #+#    #+#             */
/*   Updated: 2017/01/16 20:43:57 by ftriquet         ###   ########.fr       */
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

static void	ft_print_output_64(struct section_64 *section, void *ptr)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;

	printf("Contents of (%s,%s) section\n", section->segname, section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		printf("%016llx", (unsigned long long)section->addr + i);
		printf("\t");
		j = 17;
		while (i < section->size && --j)
			printf("%02hhx ", p[i++]);
		printf("\n");
	}
}

void		handler_64(char *ptr)
{
	unsigned int				i;
	struct segment_command_64	*seg;
	struct section_64			*sect;
	struct load_command			*lc;

	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (++i < ((struct mach_header_64 *)ptr)->ncmds)
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			if (!strcmp(seg->segname, SEG_TEXT) && (i = -1))
			{
				sect = (void *)seg + sizeof(struct segment_command_64);
				while (++i < seg->nsects)
				{
					if (!strcmp(sect->sectname, SECT_TEXT))
						return (ft_print_output_64(sect, ptr));
					sect = (void *)sect + sizeof(*sect);
				}
			}
			lc = (void *)lc + lc->cmdsize;
		}
}

static void	ft_print_output_32(struct section *section, void *ptr)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;

	printf("Contents of (%s,%s) section\n", section->segname, section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		printf("%08llx", (unsigned long long)section->addr + i);
		printf("\t");
		j = 17;
		while (i < section->size && --j)
			printf("%02hhx ", p[i++]);
		printf("\n");
	}
}

static unsigned int	swap_bits(unsigned int c)
{
	return (((c & 0xFF) << 24) | (((c >> 8) & 0xFF) << 16) |
			(((c >> 16) & 0xFF) << 8) | ((c >> 24) & 0xFF));
}

void		handler_32(char *ptr)
{
	unsigned int			i;
	struct segment_command	*seg;
	struct section			*sect;
	struct load_command		*lc;

	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header);
	while (++i < ((struct mach_header *)ptr)->ncmds)
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			if (!strcmp(seg->segname, SEG_TEXT) && (i = -1))
			{
				sect = (void *)seg + sizeof(struct segment_command);
				while (++i < seg->nsects)
				{
					if (!strcmp(sect->sectname, SECT_TEXT))
						return (ft_print_output_32(sect, ptr));
					sect = (void *)sect + sizeof(*sect);
				}
			}
			lc = (void *)lc + lc->cmdsize;
		}
}

int			ft_otool_dylib(char *ptr, t_slice *list, char *name);
int			ft_otool_fat(char *ptr, char *name, int swap);

void		ft_otool(char *ptr)
{
	unsigned int	magic_number;
	t_slice				*list;

	magic_number = *(int *)ptr;
	list = ft_new_slice(15);
	if (magic_number == MH_MAGIC_64)
		handler_64(ptr);
	else if (magic_number == MH_MAGIC)
		handler_32(ptr);
	else if (magic_number == MH_DYLIB)
		ft_otool_dylib(ptr, list, "");
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		ft_otool_fat(ptr, NULL, (magic_number == FAT_CIGAM));
	else {
		ft_dprintf(STDERR_FILENO, "The file is not a valid binary\n");
	}
}

static intmax_t		get_value(intmax_t value, intmax_t swap)
{
	return swap ? swap_bits(value) : value;
}

int			ft_otool_fat(char *ptr, char *name, int swap)
{
	struct fat_header		*h;
	struct fat_arch			*arch;
	uint32_t				offset;
	struct mach_header_64 	*header;
	size_t					i;
	(void)name;

	h = (struct fat_header *)ptr;
	arch = (void *)h + sizeof(*h);
	offset = get_value(arch->offset, swap);
	i = 0;
	while ((int)i < get_value(h->nfat_arch, swap))
	{
		if (get_value(arch->cputype, swap) == CPU_TYPE_X86_64)
		{
			offset = get_value(arch->offset, swap);
			header = (void *)ptr + offset;
			break;
		}
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	header = (void *)ptr + offset;
	ft_otool((void *)header);
	return (1);
}

int			ft_otool_dylib(char *ptr, t_slice *list, char *name)
{
	if (name)
		ft_printf("\n%s:\n", name);
	(void)ptr;
	(void)list;
	return (0);
}

int			ft_openfile(int fd)
{
	char			*ptr;
	struct stat		buf;

	if (fstat(fd, &buf) < 0 || (ptr = mmap(0, buf.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("system failed");
		return (EXIT_FAILURE);
	}
	ft_otool(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("munmap failed");
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
		printf("Usage %s <files>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	while (++i < argc)
	{
		printf("%s:\n", argv[i]);
		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{
			puts("open failed");
			return (EXIT_FAILURE);
		}
		if ((fd = ft_openfile(fd)))
			return (fd);
	}
	return (EXIT_SUCCESS);
}
