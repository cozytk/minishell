/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 04:24:37 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/11 17:46:27 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_len;
	size_t	lit_len;

	if (*little == 0)
		return ((char *)big);
	else if (len == 0)
		return (0);
	big_len = ft_strlen(big);
	lit_len = ft_strlen(little);
	if (len > big_len)
		len = big_len;
	while (len-- - lit_len + 1 && *big)
	{
		if (ft_strncmp(big, little, lit_len) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
