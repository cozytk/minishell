/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:50:32 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/06 17:44:18 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int dst_len;
	int	src_len;
	int	result;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	result = dst_len + src_len;
	if (dst_len >= (int)size)
		return (src_len + (int)size);
	else if ((int)size < src_len + dst_len + 1)
	{
		src_len = size - dst_len - 1;
		if (src_len < 0)
			src_len = 0;
	}
	while ((dst_len < result) && src_len--)
		dst[dst_len++] = *(src++);
	dst[dst_len] = '\0';
	return (result);
}
