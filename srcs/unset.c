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

int		is_identifier(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 21 && str[i] < 48) || \
			(str[i] > 57 && str[i] < 65) || \
			(str[i] > 90 && str[i] < 97) || \
			(str[i] > 122 && str[i] < 127))
			return (1);
		i++;
	}
	return (0);
}

int 	write_unset_error(char *str, char *err, t_all *a, int exit)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	ft_putendl_fd(err, 2);
	g_end = exit;
	a->cd = 0;
	return (g_end);
}

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
			if (same_key(a->env[j], mat[i]))
			{
				a->env = ft_delete_row(a->env, j);
				break ;
			}
		}
		if (!a->env[j] && is_identifier(mat[i]))
			write_unset_error(mat[i], ": not a valid identifier", a, 1);
	}
}

void	parse_unset(t_all *a)
{
	a->arg = check_overlap(a->arg);
	delete_env(a->arg, a);
	ft_free_mat(a->arg);
	a->arg = NULL;
}

int		unset(t_all *a)
{
	if (!ft_strncmp(a->cmd, "unset\0", 6))
	{
		if (!a->arg)
			return (1);
		parse_unset(a);
		ft_free_mat(a->ept);
		a->ept = NULL;
		init_export(a, a->env);
		return (1);
	}
	return (0);
}