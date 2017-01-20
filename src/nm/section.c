/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:28:40 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:28:41 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>

void		ft_build_section_list_64(t_slice *list,
		struct mach_header_64 *header)
{
	struct load_command			*lc;
	size_t						i;

	i = 0;
	lc = (void *)header + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			ft_add_segment_to_list_64((struct segment_command_64 *)lc, list);
		++i;
		lc = (void *)lc + lc->cmdsize;
	}
}

void		ft_add_segment_to_list_64(struct segment_command_64 *segment,
		t_slice *list)
{
	size_t				i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64 *)((void *)segment + sizeof(*segment));
	while (i < segment->nsects)
	{
		ft_slice_append(list, section);
		section = (void *)section + sizeof(*section);
		if (section == NULL)
			break ;
		++i;
	}
}
