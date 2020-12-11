/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:48:41 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/11 20:48:41 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**add_row(char **mat, char *arg)
{
	int		argsize;
	int		i;
	char	**new_mat;

	argsize = ft_matrow(mat);
	new_mat = malloc(sizeof(char *) * (argsize + 2));
	i = 0;
	if (mat)
	{
		while (mat[i])
		{
			new_mat[i] = ft_strdup(mat[i]);
			i++;
		}
		ft_free_mat(mat);
	}
	new_mat[i] = arg;
	new_mat[i + 1] = NULL;
	return (new_mat);
}

int		find_exact_row(char **mat, char *s)
{
	int		i;

	if (!mat)
		return (-1);
	i = 0;
	while (mat[i])
	{
		if (!ft_strncmp(mat[i], s, ft_strlen(s) + 1))
			return (i);
		i++;
	}
	return (-1);
}

int 	find_row(char **mat, char *s)
{
	int		i;

	if (!mat)
		return (-1);
	i = 0;
	while (mat[i])
	{
		if (!ft_strncmp(mat[i], s, ft_strlen(s)))
			return (i);
		i++;
	}
	return (-1);
}
char	**ft_delete_row(char **mat, int del)
{
	char	**tmp;
	int		row;
	int		i;
	int		j;

	i = -1;
	j = -1;
	row = ft_matrow(mat);
	if (row < 2)
	{
		ft_free_mat(mat);
		return ((void *)0);
	}
	if (!(tmp = (char **)malloc(sizeof(char *) * row)))
		exit(1);
	while (++j < row)
	{
		if (j == del)
			continue ;
		tmp[++i] = ft_strdup(mat[j]);
	}
	tmp[row - 1] = (void *)0;
	ft_free_mat(mat);
	mat = (void *)0;
	return (tmp);
}
