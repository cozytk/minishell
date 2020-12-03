/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:05:17 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/29 23:05:18 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 	delete_env(char **mat, t_all *a)
{
	int i;
	int j;

	i = -1;
	while (mat[++i])
	{
		j = -1;
		while (a->env[++j])
		{
			if (!keycmp(a->env[j], mat[i]))
			{
				a->env = ft_delete_row(a->env, j);
				break ;
			}

		}
	}
}

void	parse_unset(t_all *a)
{
	check_overlap(a->arg);
	delete_env(a->arg, a);
	ft_free_mat(a->arg);
}

int		unset(t_all *a)
{
	if (!ft_strncmp(a->cmd, "unset\0", 6))
	{
		if (!a->arg)
			return (1);
		parse_unset(a);
		ft_free_mat(a->ept);
		init_export(a, a->env);
		return (1);
	}
	return (0);
}