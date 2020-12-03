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

void swap_str(char **s1, char **s2)
{
	char *temp;

	temp = ft_strdup(*s1);
	free(*s1);
	*s1 = ft_strdup(*s2);
	free(*s2);
	*s2 = ft_strdup(temp);
	free(temp);
}

void sort_mat(char **mat)
{
	int		i;
	int 	j;

	i = -1;
	while (mat[++i])
	{
		j = i;
		while (mat[++j])
		{
			if (ft_strccmp(mat[i], mat[j], '=') < 0)
				continue ;
			else if (ft_strccmp(mat[i], mat[j], '=') > 0)
				swap_str(&mat[i], &mat[j]);
			else
			{
				ft_write("Error: sort_mat\n");
				exit(1);
			}
		}
	}
}

void write_quote(char *str)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != '=')
		ft_putchar_fd(str[i], 1);
	if (!ft_strrchr(str, '='))
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	ft_write("=\"");
	while (str[++i])
		ft_putchar_fd(str[i], 1);
	ft_write("\"\n");
}
/*
 * export aaa="   aaa    " 같은 경우 quote 을 읽고나서 blank 를 -128 ~ -1 범위 사이에 문자로 처리
 */

char **ft_delete_row(char **mat, int del)
{
	char **tmp;
	int row;
	int i;
	int j;

	i = -1;
	j = -1;
	row = ft_matrow(mat);
	if (!(tmp = (char **)malloc(sizeof(char *) * row)))
		exit(1);
	while (++j < row)
	{
		if (j == del)
			continue ;
		i++;
		tmp[i] = ft_strdup(mat[j]);
	}
	tmp[row - 1] = (void *)0;
	ft_free_mat(mat);
	return (tmp);
}

char **overwrite_env(char **mat, t_all *a)
{
	int i;
	int j;

	i = -1;
//	for (int idx = 0; a->env[idx]; idx++)
//		printf("%s\n", a->env[idx]);
	while (mat[++i])
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

void check_overlap(char **mat)
{
	int i;
	int j;

	i = -1;
	while (mat[++i + 1])
	{
		j = i;
		while (mat[++j])
		{
			if (!(ft_strccmp(mat[i], mat[j], '=')))
				mat = ft_delete_row(mat, i);
		}
	}
}

void edit_env(t_all *a)
{
	char	**tmp_m;

	check_overlap(a->arg);
	a->arg = overwrite_env(a->arg, a);
	tmp_m = ft_matjoin(a->env, a->arg);
	ft_free_mat(a->env);
	ft_free_mat(a->arg);
	a->env = tmp_m;
}

void write_export(char **ept)
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

int export(t_all *a)
{
	if (!ft_strncmp(a->cmd, "export\0", 7))
	{
		if (!a->arg)
		{
			write_export(a->ept);
			return (1);
		}
		edit_env(a);
		ft_free_mat(a->ept);
		init_export(a, a->env);
		return (1);
	}
	return (0);
}

