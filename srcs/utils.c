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

char 	**ft_matadd_front(t_all *a)
{
	char	**dst;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup(a->cmd);
	tmp[1] = (void *)0;
	dst = ft_matjoin(tmp, a->arg);
	ft_free_mat(tmp);
	return (dst);
}

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
			if (ft_strccmp(mat[i], mat[j], '=') > 0)
				swap_str(&mat[i], &mat[j]);
		}
	}
}

int same_key(char *s1, char *s2)
{
	int		i;
	int		ret;
	char	*tmp1;
	char	*tmp2;

	ret = 0;
	if (!((tmp1 = malloc(ft_strlen(s1) + 1)) && (tmp2 = malloc(ft_strlen(s2) + 1))))
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
