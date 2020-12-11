/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:19:26 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/30 16:19:28 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int write_cd_error(char *str, char *err, t_all *a, int exit)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(err, 2);
	g_end = exit;
	a->cd = 0;
	return (g_end);
}

int cd_home(t_all *a, char flag)
{
	int i;

	i = find_row(a->env, "HOME=");
	if (i == -1)
	{
		if (!flag)
		{
			write_cd_error("HOME", " not set", a, 1);
			g_end = 1;
			return (1);
		}
		else if (flag == '~' && (chdir(a->init_home) == -1))
				return (write_cd_error(a->init_home,
						   ": No such file or directory", a, 127));
			return (-1);
	}
	if (chdir(a->env[i] + 5) == -1)
		return (write_cd_error(a->env[i] + 5
						 ": No such file or directory", a, 127));
	else
		g_end = 0;
	return (0);
}

int cd_oldpwd(t_all *a)
{
	int i;

	i = find_row(a->env, "OLDPWD=");
	if (i == -1)
	{
		write_cd_error("OLDPWD", " not set", a, 1);
		g_end = 1;
		return (1);
	}
	if (chdir(a->env[i] + 7) == -1)
		return (write_cd_error(a->env[i] + 7,
						 ": No such file or direcotry", a, 127));
		return (1);
}

int cd(t_all *a)
{
	if (!(ft_strncmp(a->cmd, "cd", 2)))
	{
		a->cd = 1;
		if (!a->arg)
			cd_home(a, 0);
		else if (ft_strlen(a->arg[0]) == 1 && !ft_strncmp(a->arg[0], "~", 1))
			cd_home(a, '~');
		else if (ft_strlen(a->arg[0]) == 1 && !ft_strncmp(a->arg[0], "-", 1))
			cd_oldpwd(a);
		else if (chdir(a->arg[0]) == -1)
			return (write_cd_error(a->arg[0],
						  ": No such file or direcotry", a, 127));
		return (1);
	}
	return (0);
}
