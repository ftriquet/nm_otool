/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:50:38 by akpenou           #+#    #+#             */
/*   Updated: 2016/06/02 14:58:44 by akpenou          ###   ########.fr       */
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

static void ft_print_output(struct section_64 *section, void *ptr)
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
	unsigned int				ncmds;
	struct mach_header_64		*header;
	struct segment_command_64	*seg;
	struct section_64			*sect;
	struct load_command			*lc;

	i = 0;
	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void *) ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *) lc;
			if (!strcmp(seg->segname, SEG_TEXT))
			{
				i = -1;
				sect = (void *)seg + sizeof(struct segment_command_64);
				while (++i < seg->nsects)
				{
					if (!strcmp(sect->sectname, SECT_TEXT))
					{
						ft_print_output(sect, ptr);
						break ;
					}
					sect = (void *)sect + sizeof(*sect);
				}
			}
			lc = (void *)lc + lc->cmdsize;
		}
	}
}

void		ft_otool(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *) ptr;
	if (magic_number == MH_MAGIC_64)
		handler_64(ptr);
}

int 		main(int argc, char **argv)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	fd = 0;
	if (argc == 1 && (fd = open("a.out", O_RDONLY)) < 0)
	{
		puts("no arg");
		return (-1);
	}
	else if (argc > 2)
	{
		puts("too much arg");
		return (-1);
	}
	else if (argc != 1 && (fd = open(argv[1], O_RDONLY)) < 0)
	{
		puts("open failed");
		return (-1);
	}
	if (fstat(fd, &buf) < 0)
	{
		puts("fstat failed");
		return (-1);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		puts("mmap failed");
		return (-1);
	}
	printf("%s:\n", argv[1]);
	ft_otool(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		puts("munmap failed");
		return (-1);
	}
	return (0);
}
