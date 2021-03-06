/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:28:48 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/24 21:42:44 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <nm_otool.h>
#include <libft.h>

static void	ft_print_output_32(struct section *section, void *ptr, char *name)
{
	unsigned char	*p;
	unsigned int	i;
	int				j;

	ft_printf("%s:\nContents of (%s,%s) section\n", name, section->segname,
			section->sectname);
	p = (void *)ptr + section->offset;
	i = 0;
	while (i < section->size)
	{
		ft_printf("%08llx", (unsigned long long)section->addr + i);
		ft_printf("\t");
		j = 17;
		while (i < section->size && --j)
			ft_printf("%02hhx ", p[i++]);
		ft_printf("\n");
	}
}

void		handler_32(char *ptr, char *name)
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
			sect = (void *)seg + sizeof(struct segment_command);
			while (++i < seg->nsects)
			{
				if (!ft_strcmp(sect->sectname, SECT_TEXT))
					return (ft_print_output_32(sect, ptr, name));
				sect = (void *)sect + sizeof(*sect);
			}
			lc = (void *)lc + lc->cmdsize;
		}
}
