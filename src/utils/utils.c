/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:28:50 by ftriquet          #+#    #+#             */
/*   Updated: 2017/01/20 22:30:24 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

int				ft_error(char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error: %s\n", msg);
	return (FAILURE);
}

unsigned int	swap_bytes(unsigned int c)
{
	return (((c & 0xFF) << 24) | (((c >> 8) & 0xFF) << 16) |
			(((c >> 16) & 0xFF) << 8) | ((c >> 24) & 0xFF));
}

intmax_t		get_value(intmax_t value, int swap)
{
	return (swap ? swap_bytes(value) : value);
}
