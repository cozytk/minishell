/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 23:02:24 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/03 23:02:25 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int 	ft_exit(t_all *a)
{
	if (!ft_strncmp("exit\0", a->cmd, 5))
	{
		if (a->arg)
		{
			if (a->arg[1])
			{
				ft_putendl_fd("exit", 2);
				ft_putstr_fd("bash: ", 2);
				ft_putendl_fd("exit: too many arguments", 2);
				return (1);
			}
			ft_putendl_fd("exit", 2);
			exit(ft_atoi(a->arg[0]));
		}
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	return (0);
}
