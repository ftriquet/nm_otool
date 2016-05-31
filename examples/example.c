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
void		ft_build_section_list(t_list *list, struct mach_header_64 *header);
void		ft_add_segment_to_list(struct segment_command_64 *segment,
		t_list *list);
char *str = "LOL";

char	get_type(struct nlist_64 *sym)
{
	if (sym->n_type & N_EXT)
	{
		if ((sym->n_type & N_TYPE) == N_SECT)
			return ('T');
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return 'U';
		if ((sym->n_type & N_TYPE) == N_ABS)
			return 'A';
		if ((sym->n_type & N_TYPE) == N_PBUD)
			return 'P';
		if ((sym->n_type & N_TYPE) == N_INDR)
			return 'I';
		return 'N';
	}
	else
	{
		if ((sym->n_type & N_TYPE) == N_SECT)
			return ('t');
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return 'u';
		if ((sym->n_type & N_TYPE) == N_ABS)
			return 'a';
		if ((sym->n_type & N_TYPE) == N_PBUD)
			return 'p';
		if ((sym->n_type & N_TYPE) == N_INDR)
			return 'i';
		return 'n';
	}
}

void	print_nlist64(char *stringtable, struct nlist_64 *symbol)
{
	if (!(symbol->n_type & N_STAB)) {
		ft_printf("%016llx ", symbol->n_value);
		ft_printf("%hhx ", symbol->n_type);
		ft_printf("%c ", get_type(symbol));
		ft_printf("%d ", symbol->n_sect);
		ft_printf("%s\n", stringtable + symbol->n_un.n_strx);
	}
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
	ft_printf("Nbr de lc: %d\n", ncmds);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *) lc;
			ft_printf("%s\n", segment->segname);
		}
		ft_printf("%d: %x\n", i, lc->cmd);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			ft_printf("Nbr de symboles: %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}

void	func(void *section)
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
	t_list	list;

	magic_number = *((int *)ptr);
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
		ft_list_init(&list, NULL);
		ft_build_section_list(&list, ptr);
		ft_list_iter(&list, &func);
	}
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
