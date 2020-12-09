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

	i = -1;
	row = ft_matrow(env);
	a->env = malloc(sizeof(char *) * (row + 1));
	while (++i < row)
	{
		if (!ft_strncmp(env[i], "HOME", 4))
			a->init_home = ft_strdup(ft_strchr(env[i], '/'));
		if (!ft_strncmp(env[i], "OLDPWD", 6))
			a->env[i++] = ft_strdup("OLDPWD");
		a->env[i] = ft_strdup(env[i]);
	}
	a->env[row] = (void *)0;
}

void init_export(t_all *a, char **env)
{
	if (a->ept)
		ft_free_mat(a->ept);
	a->ept = ft_matdup(env);
	sort_mat(a->ept);
}

void	parse_init(t_all *a)
{
	a->p.pipe = 0;
	a->p.s_colon = 0;
	a->p.start = a->p.i;
	a->p.candidate = NULL;
}

void    init(t_all *a)
{
	a->redirect = 0;
	a->cmd = NULL;
	a->arg = NULL;
}

void	init_index(t_all *a)
{
	a->p.i = 0;
	a->p.start = 0;
	a->p.count = 0;
	a->p.pipe = 0;
	a->p.s_colon = 0;
}
//
// Created by Taekyun Kim on 11/25/20.
//

