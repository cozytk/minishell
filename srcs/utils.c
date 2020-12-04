/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:23:10 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/29 23:23:11 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**add_row(char **mat, char *arg)
{
	int		argsize;
	int		i;
	char	**new_mat;

	if (!mat)
		return ((void *)0);
	argsize = ft_matrow(mat);
	new_mat = malloc(sizeof(char *) * (argsize + 2));
	i = 0;
	while (mat[i])
	{
		new_mat[i] = ft_strdup(mat[i]);
		i++;
	}
	ft_free_mat(mat);
	new_mat[i] = arg;
	new_mat[i + 1] = NULL;
	return (new_mat);
}

int 	find_row(char **mat, char *s)
{
	int i;

	i = 0;
	while (mat[i])
	{
		if (!ft_strncmp(mat[i], s, ft_strlen(s)))
			return (i);
		i++;
	}
	return (0);
}

void	bash_cmd_error(char *cmd, char *msg, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
	exit(exit_code);
}

int		keycmp(char *src, char *key)
{
	int i;

	i = 0;
	while (key[i])
	{
		if (src[i] != key[i])
			return (1);
		i++;
	}
	if (src[i] == '=')
		return (0);
	return (1);
}

char	*get_arg(char *str)
{
	int i;

	i = 0;
	if (!str)
		return ((void *)0);
	while (str[i] && str[i] == ' ')
		i++;
	if (i == (int)ft_strlen(str))
		exit(1);
	return (str + i);
}

int		cmd_itself(char *cmd, char *str)
{
	int len_cmd;
	int len_str;

	len_cmd = ft_strlen(cmd);
	len_str = ft_strlen(str);
	if (!ft_strncmp(str, cmd, len_cmd))
	{
		if (len_str == len_cmd)
			return (1);
		str += len_cmd;
		while (*str && *str == ' ')
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

int 	free_cmd_arg(t_all *a)
{
	if (a->cmd)
		ft_free(a->cmd);
	if (a->arg)
		ft_free(a->arg);
	return (1);
}
