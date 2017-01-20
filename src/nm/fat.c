/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:29:50 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:29:52 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <mach-o/fat.h>

int					ft_fat(char *ptr, char *name, int swap, char *errname)
{
	struct fat_header		*h;
	struct fat_arch			*arch;
	uint32_t				offset;
	struct mach_header_64	*header;
	size_t					i;

	h = (struct fat_header *)ptr;
	arch = (void *)h + sizeof(*h);
	offset = get_value(arch->offset, swap);
	i = 0;
	while ((int)i < get_value(h->nfat_arch, swap))
	{
		offset = get_value(arch->offset, swap);
		header = (void *)ptr + offset;
		if (get_value(arch->cputype, swap) == CPU_TYPE_X86_64)
			break ;
		arch = (void *)arch + sizeof(*arch);
		i++;
	}
	header = (void *)ptr + offset;
	return (ft_nm((void *)header, name, errname));
}
