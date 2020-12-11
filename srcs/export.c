/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:19:16 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/25 17:19:17 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**overwrite_env(char **mat, t_all *a)
{
	int		i;
	int		j;

	i = -1;
	if (!mat)
		return ((void *)0);
	while (mat && mat[++i])
	{
		j = -1;
		while (a->env[++j])
		{
			if (!ft_strccmp(mat[i], a->env[j], '='))
			{
				free(a->env[j]);
				a->env[j] = (void *)0;
				a->env[j] = ft_strdup(mat[i]);
				mat = ft_delete_row(mat, i);
				i = -1;
				break ;
			}
			if (i == -1)
				break ;
		}
	}
	return (mat);
}

char	**check_overlap(char **mat)
{
	int		i;
	int		j;

	i = -1;
	while (mat && mat[++i + 1])
	{
		j = i;
		while (mat[++j])
		{
			if (same_key(mat[i], mat[j]))
				return (ft_delete_row(mat, i));
		}
	}
	return (mat);
}

void	edit_env(t_all *a)
{
	char	**tmp_m;

	a->arg = check_identifier(a->arg);
	a->arg = check_overlap(a->arg);
	a->arg = overwrite_env(a->arg, a);
	tmp_m = ft_matjoin(a->env, a->arg);
	ft_free_mat(a->env);
	ft_free_mat(a->arg);
	a->arg = NULL;
	a->env = tmp_m;
}

void	write_export(char **ept)
{
	int i;

	i = -1;
	while (ept[++i])
	{
		if (!ft_strncmp(ept[i], "_=", 2))
			continue ;
		ft_write("declare -x ");
		write_quote(ept[i]);
	}
}

int		export(t_all *a)
{
	if (!ft_strncmp(a->cmd, "export\0", 7))
	{
		if (!a->arg)
		{
			write_export(a->ept);
			return (1);
		}
		edit_env(a);
		init_export(a, a->env);
		return (1);
	}
	return (0);
}

