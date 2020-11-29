/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 05:47:44 by taekkim           #+#    #+#             */
/*   Updated: 2020/04/05 04:38:09 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(long long num, int sign)
{
	long long len;

	len = 1;
	while (num >= 10)
	{
		len++;
		num = num / 10;
	}
	if (sign == -1)
		len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char		*arr;
	int			sign;
	int			len;
	long long	num;

	sign = n >= 0 ? 1 : -1;
	num = (long long)n;
	if (num < 0)
		num = -num;
	len = ft_intlen(num, sign);
	if (!(arr = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	arr[len] = '\0';
	if (num == 0)
		arr[0] = '0';
	while (num > 0)
	{
		arr[--len] = num % 10 + '0';
		num = num / 10;
	}
	if (sign == -1)
		arr[0] = '-';
	return (arr);
}
