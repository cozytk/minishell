/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:44:06 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/11 20:44:28 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_env(char **env, t_all *a)
{
	int		row;
	int		i;
	char	*home;

	i = -1;
	row = ft_matrow(env);
	a->env = malloc(sizeof(char *) * (row + 1));
	while (++i < row)
	{
		if (!ft_strncmp(env[i], "HOME", 4))
		{
			home = ft_strchr(env[i], '/');
			ft_strlcpy(a->init_home, home, ft_strlen(home) + 1);
		}
		a->env[i] = ft_strdup(env[i]);
	}
	a->env[row] = (void *)0;
	write(1, WELCOME_MSG, ft_strlen(WELCOME_MSG));
}

void	init_export(t_all *a, char **env)
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
	a->p.candidate = NULL;
	a->p.parsing = 0;
	a->p.end = 0;
	while (ft_iswhite(a->line[a->p.i]))
		a->p.i++;
	a->p.start = a->p.i;
}

void	init(t_all *a)
{
	a->redirect = 0;
	a->p.i = 0;
	a->p.pipe = 0;
	a->p.s_colon = 0;
}

void	init_struct(t_all *a)
{
	g_end = 0;
	a->cd = 0;
	a->fd_tmp = 0;
	a->redirect = 0;
	a->fileno = 0;
	a->cmd = 0;
	a->line = 0;
	a->env = 0;
	a->arg = 0;
	a->ept = 0;
	a->sub_env = 0;
}
