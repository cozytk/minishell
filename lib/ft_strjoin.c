/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:37:04 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/05 04:32:23 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	while (s1 && *s1)
		*dest++ = *s1++;
	while (s2 && *s2)
		*dest++ = *s2++;
	*dest = '\0';
	dest -= len;
	return (dest);
}
