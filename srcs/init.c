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
/* ************************************************************************* */

#include "../inc/minishell.h"

void init_env(char **env, t_all *a)
{
	int row;
	int i;
	int j;

	i = 0;
	j = 0;
	row = ft_matrow(env);
	a->env = malloc(sizeof(char *) * row);
	while (i < row)
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
			j = 1;
		a->env[i] = ft_strdup(env[i + j]);
		i++;
	}
	a->env[row - 1] = (void *)0;
}

void init_export(t_all *a, char **env)
{
//	char **tmp;
//
//	tmp = ft_matdup(mat);
//	if (find_row(env, "OLDPWD"))
//		env = add_row(env, "OLDPWD");
	a->ept = ft_matdup(env);
	a->ept = add_row(a->ept, ft_strdup("OLDPWD"));
	sort_mat(a->ept);
}


//
// Created by Taekyun Kim on 11/25/20.
//

