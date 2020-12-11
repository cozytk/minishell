/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:05:27 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/11 19:53:37 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_echo(t_all *a)
{
	int i;
	int	size;
	int enter;

	i = 0;
	enter = 1;
	size = ft_matrow(a->arg) - 1;
	if (!ft_strncmp(a->arg[i], "-n", 2))
	{
		enter = 0;
		i++;
	}
	while (a->arg[i])
	{
		ft_putstr_fd(a->arg[i], 1);
		if (i != size)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (enter)
		ft_putchar_fd('\n', 1);
}

int		echo(t_all *a)
{
	if (!ft_strncmp(a->cmd, "echo\0", 5))
	{
		if (!a->arg)
			ft_putchar_fd('\n', 1);
		else
			write_echo(a);
		return (1);
	}
	return (0);
}
