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

void write_export(char *str)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != '=')
		ft_putchar_fd(str[i], 1);
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

	i = 0;
	j = 0;
	row = ft_matrow(mat);
	if (!(tmp = (char **)malloc(sizeof(char *) * row)))
		exit(1);
	while (j < row)
	{
		if (i != del)
			i++;
		j++;
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
	while (mat[++i])
	{
		j = -1;
		while (a->env[++j])
		{
			if (!ft_strccmp(mat[i], a->env[i], '='))
			{
				free(a->env[i]);
				a->env[i] = (void *)0;
				a->env[i] = ft_strdup(mat[i]);
				mat = ft_delete_row(mat, i);
			}
		}
	}
	return (mat);
}

void check_overlap(char **mat)
{
	int i;
	int j;

	i = -1;
	j = -1;
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

void edit_env(char *str, t_all *a)
{
	char	*temp;
	char	**mat;
	char	**tmp_m;

	if (!(temp = malloc(ft_strlen(str) + 1)))
		exit(1);
	ft_strlcpy(temp, str + 7, ft_strlen(str + 7) + 1);
	mat = ft_split(temp, ' ');
	check_overlap(mat);
	mat = overwrite_env(mat, a);
	tmp_m = ft_matjoin(a->env, mat);
	ft_free_mat(a->env);
	a->env = tmp_m;
	free(temp);
}

int export(char *str, t_all *a)
{
	int i;

	i = -1;
	if (ft_strlen(str) == 6 && !ft_strncmp(str, "export", 6))
	{
		while (a->ept[++i])
		{
			if (!ft_strncmp(a->ept[i], "_=", 2))
				continue ;
			ft_write("declare -x ");
			write_export(a->ept[i]);
		}
	}
	/*
	 * export x=y
	 * export x=y a=b
	 * 등등 정상적인 케이스로 들어왔다고 가정k
	 */
	else
	{
		edit_env(str, a);
		ft_free_mat(a->ept);
		init_export(a, a->env);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all a;
	char *line;
	(void)argc;
	(void)argv;

	init_env(envp, &a);
	init_export(&a, a.env);
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '\n')
		{
			line = (void *)0;
			free(line);
			continue;
		}
		if (!ft_strncmp("exit", line, 4))
			exit(0);
		export(line, &a);
		line = (void *)0;
		free(line);
	}
	return (0);
}
