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

int		write_exit_error(t_all *a, int flag)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bash: ", 2);
	if (flag)
	{
		ft_putstr_fd(a->arg[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	ft_putendl_fd("exit: too many arguments", 2);
}

int 	is_num_arg(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_exit(t_all *a)
{
	if (!ft_strncmp("exit\0", a->cmd, 5))
	{
		if (a->arg)
		{
			if (!is_num_arg(a->arg[0]))
			{
				write_exit_error(a, 1);
				exit(255);
			}
			if (a->arg[1])
			{
				write_exit_error(a, 0);
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
