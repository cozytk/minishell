/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:00:28 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/01 13:38:11 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void 	ft_free_mat(char **mat)
{
	int i;

	if (!mat)
		return ;
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i] = (void *)0;
		i++;
	}
	free(mat[i]);
	mat[i] = (void *)0;
	free(mat);
	mat = (void *)0;
}
