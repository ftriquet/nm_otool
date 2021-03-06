/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftriquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 06:14:20 by ftriquet          #+#    #+#             */
/*   Updated: 2016/03/08 22:07:00 by ftriquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H
# include <string.h>

void	*ft_memalloc(size_t size);

void	ft_memdel(void **ap);

void	ft_bzero(void *s, size_t n);

void	*ft_memccpy(void *dst, const void *src, int c, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_memset(void *b, int c, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memdup(void *ptr, size_t size);

#endif
