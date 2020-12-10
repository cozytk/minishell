/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:25:55 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/08 23:41:52 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_argument(t_all *a, char *arg)
{
	int		argsize;
	int		i;
	char	**new_mat;

	argsize = ft_matrow(a->arg);
	new_mat = malloc(sizeof(char *) * (argsize + 2));
	i = 0;
	if (a->arg)
	{
		while (a->arg[i])
		{
			new_mat[i] = ft_strdup(a->arg[i]);
			i++;
		}
		ft_free_mat(a->arg);
	}
	a->arg = NULL;
	new_mat[i] = arg;
	new_mat[i + 1] = NULL;
	a->arg = new_mat;
}

void	add_candidate(t_all *a)
{
	if (!a->p.candidate)
		return ;
	if (a->p.candidate[0] == '\0')
	{
		free(a->p.candidate);
		a->p.candidate = NULL;
		return ;
	}
	if (!a->cmd && ft_strchr(a->p.candidate, '='))
	{
		equal_process(a);
		a->p.parsing = 0;
		a->p.candidate = NULL;
		return ;
	}
	if (!a->cmd)
		a->cmd = a->p.candidate;
	else
		add_argument(a, a->p.candidate);
	a->p.candidate = NULL;
	quote_join(a);
	a->p.parsing = 0;
}

void	parse_backslash(t_all *a)
{
	if (a->p.parsing == 0)
	{
		a->p.parsing = 1;
		a->p.start = a->p.i;
	}
	a->p.i++;
	a->p.candidate = ft_strcjoin(a->p.candidate, a->line[a->p.i]);
}

int		parsing(t_all *a)
{
	parse_init(a);
	while (a->line[a->p.i])
	{
		if (is_pipe_or_scolon(a->line[a->p.i]) && a->cmd)
			return (parse_pipe_scolon(a));
		if (!ft_iswhite(a->line[a->p.i]) && a->line[a->p.i] != '\\'
				&& !is_quote(a->line[a->p.i]) && !is_sep_char(a->line[a->p.i]))
		{
			if (a->p.parsing == 0)
			{
				a->p.parsing = 1;
				a->p.start = a->p.i;
			}
			a->p.candidate = ft_strcjoin(a->p.candidate, a->line[a->p.i]);
		}
		if (a->line[a->p.i] == '\\')
			parse_backslash(a);
		else if (is_sep_char(a->line[a->p.i]))
			parse_redirect(a);
		else if (is_quote(a->line[a->p.i]))
			parse_quote(a);
		else if (ft_iswhite(a->line[a->p.i])
				|| is_pipe_or_scolon(a->line[a->p.i + 1])
				|| is_sep_char(a->line[a->p.i + 1]))
			parse_one(a);
		if (a->line[a->p.i + 1] == '\0')
			return (parse_last(a));
		a->p.i++;
	}
	return (1);
}
