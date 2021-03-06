/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:28:45 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:28:46 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <nm_otool.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <libft.h>

void	ft_print_nlist_32(char *stringtable, struct nlist *symbol,
		t_slice *list)
{
	char	type;

	if (!(symbol->n_type & N_STAB))
	{
		type = get_type_32(symbol, list);
		if (type != 'U' && type != 'u')
			ft_printf("%08llx ", symbol->n_value);
		else
			ft_putstr("         ");
		ft_printf("%c ", type);
		ft_printf("%s\n", stringtable + (symbol->n_un).n_strx);
	}
}

char	get_section_type_32(int n_sect, t_slice *sections)
{
	struct section		*section;
	int					i;

	i = 0;
	section = ft_slice_get(sections, n_sect - 1);
	while (g_type_table[i].sectname &&
			!ft_strequ(g_type_table[i].sectname, section->sectname))
		++i;
	return (g_type_table[i].symtype);
}

char	get_type_32(struct nlist *sym, t_slice *sections)
{
	if (sym->n_type & N_EXT)
	{
		if ((sym->n_type & N_TYPE) == N_SECT)
			return (ft_toupper(get_section_type_32(sym->n_sect, sections)));
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return (sym->n_value ? 'C' : 'U');
		if ((sym->n_type & N_TYPE) == N_ABS)
			return ('A');
		if ((sym->n_type & N_TYPE) == N_INDR)
			return ('I');
		return (' ');
	}
	else
	{
		if ((sym->n_type & N_TYPE) == N_SECT)
			return (get_section_type_32(sym->n_sect, sections));
		if ((sym->n_type & N_TYPE) == N_UNDF)
			return ('u');
		if ((sym->n_type & N_TYPE) == N_ABS)
			return ('a');
		if ((sym->n_type & N_TYPE) == N_INDR)
			return ('i');
		return (' ');
	}
}
