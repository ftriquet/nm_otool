#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>

/*
void		ft_build_section_list(t_list *list, struct mach_header_64 *header)
{
	struct load_command		*lc;
	struct segment_command	*segment;
	int						i;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			ft_printf("+++%s+++\n", ((struct segment_command_64 *)lc)->segname);
			ft_add_segment_to_list((struct segment_command_64 *)lc, list);
		}
		++i;
		lc = (void *)lc + lc->cmdsize;
	}
}

void		ft_add_segment_to_list(struct segment_command_64 *segment,
		t_list *list)
{
	int		i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64 *)((void *)segment + sizeof(*segment));
	while (i < segment->nsects)
	{
		ft_list_add_back(list, section);
		section = (void *)section + sizeof(*section);
		ft_printf("SECTION %s\n", section->sectname);
		if (section == NULL)
			break;
		++i;
	}
}
*/



void		ft_build_section_list(t_slice *list, struct mach_header_64 *header)
{
	struct load_command		*lc;
	struct segment_command	*segment;
	int						i;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			ft_add_segment_to_list((struct segment_command_64 *)lc, list);
		++i;
		lc = (void *)lc + lc->cmdsize;
	}
}

void		ft_add_segment_to_list(struct segment_command_64 *segment,
		t_slice *list)
{
	int		i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64 *)((void *)segment + sizeof(*segment));
	while (i < segment->nsects)
	{
		ft_slice_append(list, section);
		section = (void *)section + sizeof(*section);
		if (section == NULL)
			break;
		++i;
	}
}

