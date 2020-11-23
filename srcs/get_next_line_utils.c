/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:55:55 by taekkim           #+#    #+#             */
/*   Updated: 2020/07/27 21:25:10 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup_til_enter(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	if (!(p = (char *)malloc(ft_strlen(s1) + 1)))
		return (0);
	while (s1 && s1[i] && (s1[i] != '\n'))
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	after_enter(char **str, int spot)
{
	int i;

	i = 0;
	while (*str && (*str)[i + spot])
	{
		(*str)[i] = (*str)[i + spot];
		i++;
	}
	(*str)[i] = '\0';
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	while (s1 && s1[j])
		dest[i++] = s1[j++];
	if (s1)
	{
		free(s1);
		s1 = (void *)0;
	}
	j = 0;
	while (s2 && s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}
