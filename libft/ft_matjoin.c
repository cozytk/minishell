/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:04:10 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/29 21:04:10 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matjoin(char **m1, char **m2)
{
	char	**dst;
	int		m1_row;
	int		m2_row;
	int		i;

	m1_row = ft_matrow(m1);
	m2_row = ft_matrow(m2);
	if (!(dst = malloc(sizeof(char *) * (m1_row + m2_row + 1))))
		exit(1);
	i = -1;
	while (++i < m1_row)
		dst[i] = ft_strdup(m1[i]);
	i = -1;
	while (++i < m2_row)
		dst[m1_row + i] = ft_strdup(m2[i]);
	dst[m1_row + m2_row] = (void *)0;
	return (dst);
}
