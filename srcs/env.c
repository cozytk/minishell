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
	int oldpwd;

	i = 0;
	oldpwd = find_row(a->env, "OLDPWD");
	if (!ft_strncmp(a->env[oldpwd], "OLDPWD=", 7))
		oldpwd = -1;
	while (a->env[i])
	{
		if (i == oldpwd)
		{
			i++;
			continue ;
		}
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
