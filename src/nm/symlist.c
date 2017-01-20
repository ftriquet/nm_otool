/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:28:46 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:28:47 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

t_slice	*ft_build_symlist_64(struct mach_header_64 *header,
		int nsyms, int symoff)
{
	t_slice			*symlist;
	size_t			i;
	struct nlist_64	*symbol;

	i = 0;
	symlist = ft_new_slice(nsyms);
	symbol = (void *)header + symoff;
	while ((int)i < nsyms)
	{
		ft_slice_append(symlist, symbol + i);
		++i;
	}
	return (symlist);
}

int		ft_print_symlist_64(t_slice *symlist, t_slice *sectlist,
		char *stringtable)
{
	size_t					i;

	i = 0;
	while (i < symlist->size)
	{
		ft_print_nlist_64(stringtable, ft_slice_get(symlist, i), sectlist);
		++i;
	}
	return (1);
}

t_slice	*ft_build_symlist_32(struct mach_header *header, int nsyms, int symoff)
{
	t_slice			*symlist;
	size_t			i;
	struct nlist	*symbol;

	i = 0;
	symlist = ft_new_slice(nsyms);
	symbol = (void *)header + symoff;
	while ((int)i < nsyms)
	{
		ft_slice_append(symlist, symbol + i);
		++i;
	}
	return (symlist);
}

int		ft_print_symlist_32(t_slice *symlist, t_slice *sectlist,
		char *stringtable)
{
	size_t					i;

	i = 0;
	while (i < symlist->size)
	{
		ft_print_nlist_32(stringtable, ft_slice_get(symlist, i), sectlist);
		++i;
	}
	return (1);
}
