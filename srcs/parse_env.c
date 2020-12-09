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

char	*get_env_by_arg2(char *arg, int *count, int i)
{
	int		start;

	if (arg[i] == '$' && arg[i + 1] == '{')
	{
		start = i + 2;
		while (arg[i] != '}' && arg[i])
			i++;
		*count = i;
		if (!arg[i])
			return (NULL);
		return (ft_substr(arg, start, i - start));
	}
	else if (arg[i] == '$')
	{
		start = i + 1;
		while (arg[i] && arg[i] != ' ' && ft_isalnum(arg[i + 1]))
			i++;
		*count = i;
		return (ft_substr(arg, start, i - start + 1));
	}
	return (NULL);
}

char	*get_env_by_arg(char *arg, int *count)
{
	int		i;
	char	*env;

	i = 0;
	while (arg[i])
	{
		env = get_env_by_arg2(arg, count, i);
		if (env)
			return (env);
		i++;
	}
	return (NULL);
}

char	*find_env_result(t_all *a, char *env)
{
	int		i;
	int		j;
	int		start;
	char	*temp;

	i = 0;
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
			a->p.tmp2 = find_env_result(a, env);
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
