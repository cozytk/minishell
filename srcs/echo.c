/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:05:27 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/30 01:05:29 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 	write_echo(char *str)
{
	int enter;

	enter = 1;
	while (*str && *str == ' ')
		str++;
	if (!ft_strncmp(str, "-n ", 3))
	{
		enter = 0;
		str += 3;
	}
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		while (*str && *str != ' ')
			ft_putchar_fd(*str++, 1);
		ft_putchar_fd(' ', 1);
	}
	if (enter)
		ft_putchar_fd('\n', 1);
}

int 	echo(char *str)
{
	if (cmd_itself("echo", str))
		ft_putchar_fd('\n', 1);
	else if (!ft_strncmp("echo ", str, 5))
		write_echo(str + 5);
	return (1);
}