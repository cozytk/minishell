/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:15:41 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/09 00:23:36 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*env_g_end(char *env)
{
	free(env);
	return (ft_itoa(g_end));
}

char	*find_env_result(t_all *a, char *env, int i, int j)
{
	int		start;
	char	*temp;

	if (!ft_strncmp(env, "$\0", 2) || ft_isdigit(env[0]))
		return (env);
	while (a->env[i])
	{
		if (!ft_strncmp(a->env[i], env, ft_strlen(env)))
		{
			j = 0;
			while (a->env[i][j] != '=' && a->env[i][j])
				j++;
			j++;
			start = j;
			while (a->env[i][j])
				j++;
			temp = ft_substr(a->env[i], start, j - start);
			free(env);
			return (temp);
		}
		i++;
	}
	free(env);
	return (NULL);
}

char	*env_appending(t_all *a, char *arg, int count)
{
	char	*env;
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (arg[i])
	{
		if (arg[i] != '$')
			result = ft_strcjoin(result, arg[i]);
		else
		{
			a->p.tmp = result;
			env = get_env_by_arg(&arg[i], &count);
			a->p.tmp2 = find_env_result(a, env, 0, 0);
			result = ft_strjoin(result, a->p.tmp2);
			free(a->p.tmp);
			free(a->p.tmp2);
			i += count;
			if (!arg[i])
				break ;
		}
		i++;
	}
	return (result);
}

void	process_env(t_all *a, char *arg)
{
	char	*result;
	int		size;

	result = env_appending(a, arg, 0);
	size = ft_matrow(a->arg) - 1;
	a->arg = ft_delete_row(a->arg, size);
	add_argument(a, result);
}
