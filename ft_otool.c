/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 15:50:38 by akpenou           #+#    #+#             */
/*   Updated: 2016/06/01 23:47:05 by akpenou          ###   ########.fr       */
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

static void ft_print_output(struct section_64 *section)
{
	unsigned char	*p;
	uint64_t		i;
	int				j;

	printf("-----------------------------------------------------\n");
	printf("(%s,%s) section\n", section->segname, section->sectname);
	p = (void *)section ;
	i = 0;

	while (i < section->size)
	{
		printf("%016llx ", p + i);
		j = 17;
		while (i < section->size && --j)
	//		i++;
			printf("%02hhx ", p[i++]);
		printf("\n");
	}
}

void		handler_64(char *ptr)
{
	int							i;
	int							ncmds;
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
			printf("----------------------------------------------------- %p\n", seg);
			printf("cmd %x\n", seg->cmd);						/* LC_SEGMENT_64 */
			printf("cmdsize %x\n", seg->cmdsize);				/* includes sizeof section_64 structs */
			printf("segname[16] %s\n", (char *)seg->segname);	/* segment name */
			printf("vmaddr %llx\n", seg->vmaddr);				/* memory address of this segment */
			printf("vmsize %llx\n", seg->vmsize);				/* memory size of this segment */
			printf("fileoff %llx\n", seg->fileoff);				/* file offset of this segment */
			printf("filesize %llx\n", seg->filesize);			/* amount to map from the file */
			printf("nsects %x\n", seg->nsects);					/* number of sections in segment */
			printf("flags %x\n", seg->flags);					/* flags */
			if (!strcmp(seg->segname, SEG_TEXT))
			{
				i = -1;
				sect = (void *)seg + sizeof(struct segment_command_64);
				while (++i < seg->nsects)
				{
					printf("------------------ SECTION -----------------%p\n", sect);
					printf("sectname[16] %s\n", sect->sectname);	/* name of this section */
					printf("segname[16] %s\n", sect->segname);		/* segment this section goes in */
					printf("addr %p\n", sect->addr);					/* memory address of this section */
					printf("size %llx\n", sect->size);					/* size in bytes of this section */
					printf("offset %x\n", sect->offset);				/* file offset of this section */
					printf("align %x\n", sect->align);					/* section alignment (power of 2) */
					printf("reloff %x\n", sect->reloff);				/* file offset of relocation entries */
					printf("nreloc %d\n", sect->nreloc);				/* number of relocation entries */
					printf("flags %x\n", sect->flags);					/* flags (section type and attributes)*/
					printf("reserved1 %x\n", sect->reserved1);			/* reserved (for offset or index) */
					printf("reserved2 %x\n", sect->reserved2);			/* reserved (for count or sizeof) */
					printf("reserved3 %x\n", sect->reserved3);			/* reserved */
					if (!strcmp(sect->sectname, SECT_TEXT))
					{
						ft_print_output(sect);
						break ;
					}
					sect = (void *)sect + sizeof(*sect);
				}
			}
			lc = (void *)lc + lc->cmdsize;
		}
	}
}

void		nm(char *ptr)
{
	int						magic_number;

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
	printf("size = %x\n", buf.st_size);
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		puts("munmap failed");
		return (-1);
	}
	return (0);
}
