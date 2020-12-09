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
	return (0);
}

int 	exec_cd(t_all *a)
{
	int i;

	i = 0;
	if (!ft_strncmp(a->arg[0], "~\0", 2) && !a->arg[1])
	{
		while (a->env[i])
		{
			if (!ft_strncmp(a->env[i], "HOME=", 5))
			{
				if (chdir(a->env[i] + 5) == -1)
					return (write_cd_error(a->env[i] + 5));
			}
			i++;
			if (!a->env[i])
				return (0);
		}
	}
	else if (chdir(a->arg[0]) == -1)
		return (write_cd_error(a->arg[0]));
	return (0);
}

int		cd_home(t_all *a, char flag)
{
	int i;

	i = find_row(a->env, "HOME");
	if (i == -1)
	{
		if (!flag)
		{
			ft_putendl_fd("bash: cd: HOME not set", 2);
			return (0);
		}
		else if (flag == '~' && (chdir(a->init_home) == -1))
				return (write_cd_error(a->init_home));
		return (1);
	}
	if (chdir(a->env[i] + 5) == -1)
		return (write_cd_error(a->env[i] + 5));
	return (0);
}

int 	cd(t_all *a)
{
	if (!(ft_strncmp(a->cmd, "cd", 2)))
	{
		if (!a->arg)
			cd_home(a, 0);
		else if (!ft_strncmp(a->arg[0], "~", 0) && (ft_strlen(a->arg[0]) == 1))
		{
			a->arg = malloc(sizeof(char *) * 2);
			a->arg[0] = ft_strdup("~");
			a->arg[1] = (void *)0;
			exec_cd(a);
			ft_free_mat(a->arg);
			a->arg = NULL;
			return (1);
		}
		exec_cd(a);
		return (1);
	}
	return (0);
}
