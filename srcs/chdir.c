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

int 	write_cd_error(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
	g_end = 127;
	return (g_end);
}

int		cd_home(t_all *a, char flag)
{
	int i;

	i = find_row(a->env, "HOME=");
	if (i == -1)
	{
		if (!flag)
		{
			ft_putendl_fd("bash: cd: HOME not set", 2);
			g_end = 1;
			return (1);
		}
		else if (flag == '~' && (chdir(a->init_home) == -1))
				return (write_cd_error(a->init_home));
		return (-1);
	}
	if (chdir(a->env[i] + 5) == -1)
		return (write_cd_error(a->env[i] + 5));
	else
		g_end = 0;
	return (0);
}

int 	cd(t_all *a)
{
	if (!(ft_strncmp(a->cmd, "cd", 2)))
	{
		if (!a->arg)
			cd_home(a, 0);
		else if (ft_strlen(a->arg[0]) == 1 && !ft_strncmp(a->arg[0], "~", 1))
			cd_home(a, '~');
		else if (chdir(a->arg[0]) == -1)
			return (write_cd_error(a->arg[0]));
		return (1);
	}
	return (0);
}
