/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:41:12 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/25 19:41:13 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matdup(char **mat)
{
	char	**temp;
	int		row;
	int		i;

	i = 0;
	row = 0;
	while (mat[row])
		row++;
	if (!(temp = (char **)malloc(sizeof(char *) * row)))
		exit(1);
	while (i < row)
	{
		temp[i] = ft_strdup(mat[i]);
		i++;
	}
	return (temp);
}
