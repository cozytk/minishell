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

void	parse_unset(char *str, t_all *a)
{
	char	*temp;
	char	**mat;

	if (!(temp = malloc(ft_strlen(str) + 1)))
		exit(1);
	ft_strlcpy(temp, str + 6, ft_strlen(str + 6) + 1);
	mat = ft_split(temp, ' ');
	check_overlap(mat);
	delete_env(mat, a);
	ft_free_mat(mat);
	free(temp);
}

int		unset(char *str, t_all *a)
{
	if (cmd_itself("unset", str))
		return (1);
	else if (!ft_strncmp("unset ", str, 6))
	{
		parse_unset(str, a);
		ft_free_mat(a->ept);
		init_export(a, a->env);
	}
	return (1);
}