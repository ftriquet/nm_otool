/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:28:41 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:28:43 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>

void		ft_build_section_list_32(t_slice *list, struct mach_header *header)
{
	struct load_command		*lc;
	unsigned int			i;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			ft_add_segment_to_list_32((struct segment_command *)lc, list);
		++i;
		lc = (void *)lc + lc->cmdsize;
	}
}

void		ft_add_segment_to_list_32(struct segment_command *segment,
		t_slice *list)
{
	unsigned int	i;
	struct section	*section;

	i = 0;
	section = (struct section *)((void *)segment + sizeof(*segment));
	while (i < segment->nsects)
	{
		ft_slice_append(list, section);
		section = (void *)section + sizeof(*section);
		if (section == NULL)
			break ;
		++i;
	}
}
