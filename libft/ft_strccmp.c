/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:33:14 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/10 00:11:19 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strccmp(const char *s1, const char *s2, char c)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = -1;
	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while (d1[++i])
	{
		if ((d1[i] == c) && (d2[i] == c))
			return (0);
		else if ((d1[i] - d2[i] != 0) || (!(d1[i] && d2[i])))
			return (d1[i] - d2[i]);
	}
	return (0);
}
