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

void 	write_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

int 	env(char *str, t_all *a)
{
	if (cmd_itself("env", str))
	{
		write_env(a->env);
		return (1);
	}
	return (0);
}
//
// Created by Taekyun Kim on 30/11/2020.
//

