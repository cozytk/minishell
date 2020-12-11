/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:38:31 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/11 18:38:32 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*equal_process2(t_all *a, char *env)
{
	int		i;

	if (((i = find_exact_row(a->env, env)) != -1) ||
			((env = ft_strcjoin(env, a->p.candidate[i]))
				&& (i = find_row(a->env, env) != -1)))
	{
		a->cmd = ft_strdup("export");
		add_argument(a, a->p.candidate);
		export(a);
		free(a->cmd);
		a->cmd = NULL;
		ft_free_mat(a->arg);
		a->arg = NULL;
	}
	else
	{
		if ((i = find_row(a->sub_env, env)) != -1)
			a->sub_env = ft_delete_row(a->sub_env, i);
		a->sub_env = add_row(a->sub_env, a->p.candidate);
	}
	return (env);
}

void	equal_process(t_all *a)
{
	char	*env;
	int		i;

	env = NULL;
	i = -1;
	while (a->p.candidate[++i] != '=')
	{
		env = ft_strcjoin(env, a->p.candidate[i]);
		i++;
	}
	env = equal_process2(a, env);
	if (env)
	{
		free(env);
		env = NULL;
	}
}
