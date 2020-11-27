/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:18:37 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/25 17:18:38 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void init_env(char **env, t_all *a)
{
	int row;
	int i;

	row = 0;
	i = 0;
	while (env[row])
		row++;
	a->env = malloc(sizeof(char *) * row + 1);
	while (i < row)
	{
		a->env[i] = ft_strdup(env[i]);
		i++;
	}
	a->env[row] = (void *)0;
}

void init_export(t_all *a, char **env)
{
	a->ept = ft_matdup(env);
	sort_mat(a->ept);
}


//
// Created by Taekyun Kim on 11/25/20.
//

