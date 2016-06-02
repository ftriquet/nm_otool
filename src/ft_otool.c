/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:50:38 by akpenou           #+#    #+#             */
/*   Updated: 2016/06/02 22:00:19 by akpenou          ###   ########.fr       */
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

static void	ft_print_output_64(struct section_64 *section, void *ptr)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;

	printf("(%s,%s) section\n", section->segname, section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		printf("%016llx ", (unsigned long long)section->addr + i);
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

	printf("(%s,%s) section\n", section->segname, section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		printf("%016llx ", (unsigned long long)section->addr + i);
		j = 17;
		while (i < section->size && --j)
			printf("%02hhx ", p[i++]);
		printf("\n");
	}
}

void		handler_32(char *ptr)
{
	unsigned int			i;
	struct segment_command	*seg;
	struct section			*sect;
	struct load_command		*lc;

	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	while (++i < ((struct mach_header *)ptr)->ncmds)
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			if (!strcmp(seg->segname, SEG_TEXT) && (i = -1))
			{
				sect = (void *)seg + sizeof(struct segment_command_64);
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

void		ft_otool(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handler_64(ptr);
	else if (magic_number == MH_MAGIC)
		handler_32(ptr);
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
