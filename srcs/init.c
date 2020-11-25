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
	int row = 0;

	while (env[row])
		row++;
	a->env = malloc(sizeof(char *) * row);
	for (int i = 0; i < row; i++)
		a->env[i] = strdup(env[i]);
}
//
// Created by Taekyun Kim on 11/25/20.
//

