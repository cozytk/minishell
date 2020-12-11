/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:42:02 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/11 18:42:03 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char *str, char c)
{
	int		size;
	int		i;
	char	*new;

	if (!str)
	{
		new = malloc(sizeof(char) * 2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	size = ft_strlen(str);
	new = malloc(sizeof(char) * (size + 2));
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	if (str)
		free(str);
	return (new);
}
