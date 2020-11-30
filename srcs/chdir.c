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

char 	*get_path(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	str = get_arg(str);
	tmp = malloc(ft_strlen(str) + 1);
	while (*str && *str == ' ')
		str++;
	while (*str && *str != ' ')
		tmp[i++] = *str++;
	tmp[i] = '\0';
	return (tmp);
}

int 	write_cd_error(char *str)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
int 	exec_cd(char *path, t_all *a)
{
	int i;

	i = 0;
	if (*path == '~' && *(path + 1) == '\0')
	{
		while (a->env[i])
		{
			if (!ft_strncmp(a->env[i], "HOME=", 5))
			{
				if (chdir(a->env[i] + 5) == -1)
					return (write_cd_error(a->env[i]));
			}
			i++;
			if (!a->env[i])
				return (0);
		}
	}
	else if (chdir(path) == -1)
		return (write_cd_error(path));
	return (0);
}

void 	parse_cd(char *str, t_all *a)
{
	char *path;

	path = get_path(str);
	exec_cd(path, a);
	free(path);
}

int 	cd(char *str, t_all *a)
{
	if (cmd_itself("cd", str))
		exec_cd("~", a);
	else if (!ft_strncmp(str, "cd ", 3))
		parse_cd(str + 3, a);
}
