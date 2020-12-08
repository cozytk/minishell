/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:45:16 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/08 23:45:18 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		parse_pipe_scolon(t_all *a)
{
	if (a->line[a->p.i - 1] != ' ' && a->p.i > 1)
		add_parsed(a, a->line);
	if (a->line[a->p.i] == '|')
		a->p.pipe = 1;
	else if (a->line[a->p.i] == ';')
		a->p.s_colon = 1;
	a->p.i++;
	a->p.start = a->p.i;
	a->p.count = 0;
	return (0);
}

void	parse_redirect(t_all *a)
{
	if (a->line[a->p.i - 1] != ' ' && a->p.i > 1)
		add_parsed(a, a->line);
	a->p.start = a->p.i;
	a->p.count = 1;
	if (a->line[a->p.i] == '>' && a->line[a->p.i + 1] == '>')
		a->p.count++;
	add_argument(a, ft_substr(a->line, a->p.start, a->p.count));
	a->p.i += a->p.count;
	a->p.start = a->p.i;
	a->p.count = -1;
	a->p.i--;
}

void	parse_quote(t_all *a)
{
	if (a->line[a->p.i - 1] != ' ' && a->p.i > 1)
		add_parsed(a, a->line);
	if (a->line[a->p.i] == '\'')
		s_quote_process(a, a->line);
	else if (a->line[a->p.i] == '\"')
		d_quote_process(a, a->line);
	a->p.start = a->p.i;
	while (is_space(a->line[a->p.i]))
	{
		a->p.i++;
		a->p.start++;
	}
	a->p.count = -1;
	a->p.i--;
}

void	parse_one(t_all *a)
{
	int		size;

	add_parsed(a, a->line);
	size = ft_matrow(a->arg) - 1;
	if (size >= 0)
		process_env(a, a->arg[size]);
	while (is_space(a->line[a->p.i]))
		a->p.i++;
	a->p.start = a->p.i;
	a->p.count = -1;
	a->p.i--;
}

int		parse_last(t_all *a)
{
	int		size;

	a->p.count++;
	add_parsed(a, a->line);
	size = ft_matrow(a->arg) - 1;
	if (size >= 0)
		process_env(a, a->arg[size]);
	return (1);
}
