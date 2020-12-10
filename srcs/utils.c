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

int 	write_error(char *cmd, char *str, char *err, int exit)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	ft_putendl_fd(err, 2);
	g_end = exit;
	return (g_end);
}

int		is_identifier(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 21 && str[i] < 48) || \
			(str[i] > 57 && str[i] < 65) || \
			(str[i] > 90 && str[i] < 97) || \
			(str[i] > 122 && str[i] < 127))
			return (1);
		i++;
	}
	return (0);
}

int same_key(char *s1, char *s2)
{
	int		i;
	int		ret;
	char	*tmp1;
	char	*tmp2;

	ret = 0;
	if (!((tmp1 = malloc(ft_strlen(s1 + 1))) && (tmp2 = malloc(ft_strlen(s2 + 1)))))
		exit(1);
	i = -1;
	while (s1[++i])
		if (s1[i] == '=')
			break ;
	ft_strlcpy(tmp1, s1, i + 1);
	i = -1;
	while (s2[++i])
		if (s2[i] == '=')
			break ;
	ft_strlcpy(tmp2, s2, i + 1);
	if (((int)ft_strlen(tmp1) == i) && !ft_strncmp(tmp1, tmp2, i))
		ret = 1;
	free(tmp1);
	free(tmp2);
	return (ret);
}

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
	return (-1);
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
