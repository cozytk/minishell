/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:23:10 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/29 23:23:11 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		keycmp(char *src, char *key)
{
	int i;

	i = 0;
	while (key[i])
	{
		if (src[i] != key[i])
			return (1);
		i++;
	}
	if (src[i] == '=')
		return (0);
	return (1);
}

char	*get_arg(char *str)
{
	int i;

	i = 0;
	if (!str)
		return ((void *)0);
	while (str[i] && str[i] == ' ')
		i++;
	if (i == ft_strlen(str))
		exit(1);
	return (str + i);
}

int		cmd_itself(char *cmd, char *str)
{
	int len_cmd;
	int len_str;

	len_cmd = ft_strlen(cmd);
	len_str = ft_strlen(str);
	if (!ft_strncmp(str, cmd, len_cmd))
	{
		if (len_str == len_cmd)
			return (1);
		str += len_cmd;
		while (*str && *str == ' ')
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

