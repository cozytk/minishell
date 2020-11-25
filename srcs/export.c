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

void sort_mat(char ***env)
{
	int		i;
	int 	j;

	i = -1;
	while ((*env)[++i])
	{
		j = i;
		while ((*env)[++j])
		{
			if (ft_strccmp((*env)[i], (*env)[j], '=') < 0)
				continue ;
			else if (ft_strccmp((*env)[i], (*env)[j], '=') > 0)
				swap_str(&(*env)[i], &(*env)[j]);
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
		printf("%c", str[i]);
//		ft_write(&str[i]);
//	ft_write("=\"");
	printf("%s", "=\"");
	while (str[++i])
		printf("%c", str[i]);
	printf("%s", "\"");
	while (str[++i])
	printf("\n");
//		ft_write(&str[i]);
//	ft_write("\"");
}

int export(char *str, t_all *a)
{
	int i;

	i = -1;
	if (!ft_strncmp(str, "export", 6))
	{
		sort_mat(&a->env);
		while (a->env[++i])
		{
			if (!ft_strncmp(a->env[i], "_=", 2))
				continue ;
//			ft_write("declare -x ");
//			ft_write(a->env[i]);
			write_export(a->env[i]);
//			ft_write("\n");
		}
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all a;
	(void)argc;
	(void)argv;

	init_env(envp, &a);
	if (!export("export", &a))
		puts("error\n");
	return (0);
}
// Created by Taekyun Kim on 11/24/20.
//

