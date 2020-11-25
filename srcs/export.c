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
//
//void sort_mat(char ***env)
//{
//	int		i;
//	int 	j;
//
//	i = -1;
//	while ((*env)[++i])
//	{
//		j = i;
//		while ((*env)[++j])
//		{
//			if (ft_strccmp((*env)[i], (*env)[j], '=') < 0)
//				continue ;
//			else if (ft_strccmp((*env)[i], (*env)[j], '=') > 0)
//				swap_str(&(*env)[i], &(*env)[j]);
//			else
//				exit(1);
//		}
//	}
//}

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
				exit(1);
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
//	else
//		add_export(str, &a->env);
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all a;
	(void)argc;
	(void)argv;

	init_env(envp, &a);
	init_export(&a, a.env);
	if (!export("export", &a))
		puts("error\n");
	return (0);
}
// Created by Taekyun Kim on 11/24/20.
//

