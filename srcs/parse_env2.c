/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:06:47 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/09 21:06:49 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_by_arg3(char *arg, int *count, int i)
{
	if (arg[i] == '$' && arg[i + 1] == '\0')
	{
		*count = 1;
		return (ft_strdup("$"));
	}
	else if (arg[i] == '$' && arg[i + 1] == '$')
	{
		*count = 1;
		return (ft_strdup("12345"));
	}
	else if (arg[i] == '$' && arg[i + 1] == '?')
	{
		*count = 1;
		return (ft_itoa(g_end));
	}
	return (NULL);
}

char	*get_env_by_arg2(char *arg, int *count, int i)
{
	int		start;
	char	*temp;

	if ((temp = get_env_by_arg3(arg, count, i)) != NULL)
		return (temp);
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
