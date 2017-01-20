#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <nm_otool.h>
#include <libft.h>

static void	ft_print_output_64(struct section_64 *section, void *ptr, char *name)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;

	printf("%s:\nContents of (%s,%s) section\n", name, section->segname, section->sectname);
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

void		handler_64(char *ptr, char *name)
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
						return (ft_print_output_64(sect, ptr, name));
					sect = (void *)sect + sizeof(*sect);
				}
			}
			lc = (void *)lc + lc->cmdsize;
		}
}
