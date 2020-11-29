/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:25:31 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/10 01:39:16 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (!(a || b))
		return (dst);
	while (n--)
		*a++ = *b++;
	return (dst);
}
