/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:56:21 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/13 20:10:24 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		start_idx(char const *str, char const *sep)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (sep[j] && str[i])
	{
		if (str[i] == sep[j])
		{
			if (i == (int)ft_strlen(str) - 1)
				return (-1);
			i++;
			j = 0;
			continue;
		}
		j++;
	}
	return (i);
}

int		end_idx(char const *str, char const *sep)
{
	int i;
	int j;

	i = ft_strlen(str) - 1;
	j = 0;
	while (sep[j] && str[i])
	{
		if (str[i] == sep[j])
		{
			if (i == 0)
				return (-1);
			i--;
			j = 0;
			continue;
		}
		j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*dest;
	int		i;

	i = 0;
	start = start_idx(s1, set);
	end = end_idx(s1, set);
	if (start < 0 || end < 0)
	{
		dest = (char *)ft_calloc(1, sizeof(char));
		*dest = 0;
		return (dest);
	}
	if (!(dest = (char *)malloc(sizeof(char) * end - start + 2)))
		return (0);
	dest[end - start + 1] = '\0';
	while (i < end - start + 1)
	{
		dest[i] = s1[i + start];
		i++;
	}
	return (dest);
}
