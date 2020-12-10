/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 00:23:02 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/30 00:23:03 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 	write_env(t_all *a)
{
	int i;

	i = 0;
	while (a->env[i])
	{
		ft_putendl_fd(a->env[i], 1);
		i++;
	}
}

int 	env(t_all *a)
{
	if (!ft_strncmp(a->cmd, "env\0", 4))
	{
		write_env(a);
		return (1);
	}
	return (0);
}
