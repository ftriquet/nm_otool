/* Google: Mach-O File Format: */
/* https://developer.apple.com/library/mac/documentation/DeveloperTools/Conceptual/MachORuntime/Reference/reference.html */

/* http://sourceforge.net/projects/machoview */


/* /usr/include/mach-o/loader.h */
/* /usr/include/mach-o/nlist.h */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

int		dump_header_64(struct mach_header_64 *header);
int	dump_header(void *header_ptr);
char *str = "LOL";

char	get_type(uint8_t n_sect)
{
	if (n_sect == 1)
		return 'T';
	if (n_sect == 0)
		return 'U';
	if (n_sect == 9)
		return 'D';
	if (n_sect == 8)
		return 'S';
	return ' ';
}

void	print_nlist64(char *stringtable, struct nlist_64 *symbol)
{
	ft_printf("%016llx ", symbol->n_value);
	ft_printf("%hhx ", symbol->n_type);
	ft_printf("%c ", get_type(symbol->n_sect));
	ft_printf("%d ", symbol->n_sect);
	ft_printf("%s\n", stringtable + symbol->n_un.n_strx);
}

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int				i;
	struct nlist_64	*array;
	char			*stringtable;

	i = 0;
	array = (void *)ptr + symoff;
	stringtable = ptr + stroff;
	while (i < nsyms)
	{
		print_nlist64(stringtable, array + i);
		++i;
	}
}

void handle_64(char *ptr)
{
	struct mach_header_64	*header;
	int						ncmds;
	struct load_command		*lc;
	int						i;
	struct symtab_command	*sym;
	struct segment_command_64	*segment;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		segment = (struct segment_command_64 *) lc;
		puts(segment->segname);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			ft_printf("Nbr de symboles: %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}

void	nm(char *ptr)
{
	int		magic_number;

	magic_number = *((int *)ptr);
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	dump_header(ptr);
}

int main(int ac, char **av)
{
	struct stat	buf;
	int			fd;
	char		*ptr;
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
