/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slices_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 00:20:44 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:52:28 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

static void	*cp(void *elem)
{
	return (elem);
}

static void	do_nothing(void *elem)
{
	(void)elem;
}

static void	ft_merge_slices(t_slice *main, t_slice **slices,
		int (*cmp)(void *, void *, char *), char *strtable)
{
	size_t		i;
	size_t		j;
	size_t		k;
	t_slice		*left;
	t_slice		*right;

	i = 0;
	j = 0;
	k = 0;
	left = slices[0];
	right = slices[1];
	while (i < left->size && j < right->size)
	{
		if ((*cmp)(ft_slice_get(left, i), ft_slice_get(right, j), strtable) < 0)
			ft_slice_put(main, ft_slice_get(left, i++), k);
		else
			ft_slice_put(main, ft_slice_get(right, j++), k);
		++k;
	}
	while (i < left->size)
		ft_slice_put(main, ft_slice_get(left, i++), k++);
	while (j < right->size)
		ft_slice_put(main, ft_slice_get(right, j++), k++);
}

void		ft_slice_merge_sort(t_slice *slice,
		int (*cmp)(void *, void *, char *), char *strtable)
{
	t_slice			*left;
	t_slice			*right;
	t_slice			*slices[2];

	if (slice->size <= 1)
		return ;
	left = ft_slice_slice(slice, -1, slice->size / 2, &cp);
	right = ft_slice_slice(slice, slice->size / 2, -1, &cp);
	slices[0] = left;
	slices[1] = right;
	ft_slice_merge_sort(left, cmp, strtable);
	ft_slice_merge_sort(right, cmp, strtable);
	ft_merge_slices(slice, slices, cmp, strtable);
	ft_slice_delete(&left, &do_nothing);
	ft_slice_delete(&right, &do_nothing);
}
