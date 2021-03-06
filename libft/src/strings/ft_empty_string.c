/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:04:08 by ftriquet          #+#    #+#             */
/*   Updated: 2016/02/27 06:21:44 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_boolean.h>

int		ft_empty_string(const char *s)
{
	while (*s)
	{
		if (ft_isblank(*s) == 0)
			return (0);
		++s;
	}
	return (1);
}
