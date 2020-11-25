/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 04:33:04 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/09 22:56:06 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (!(a || b))
		return (dst);
	if (dst < src)
	{
		while (len--)
			*a++ = *b++;
	}
	else
	{
		a += len;
		b += len;
		while (len--)
			*--a = *--b;
	}
	return (dst);
}
