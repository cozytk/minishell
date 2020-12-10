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
	if (a->p.candidate)
		add_candidate(a);
	if (a->line[a->p.i] == '|')
		a->p.pipe = 1;
	else if (a->line[a->p.i] == ';')
		a->p.s_colon = 1;
	a->p.i++;
	return (0);
}

void	parse_redirect(t_all *a)
{
	a->p.candidate = ft_strcjoin(a->p.candidate, a->line[a->p.i]);
	a->p.i++;
	if (a->line[a->p.i] == '>')
	{
		a->p.candidate = ft_strcjoin(a->p.candidate, a->line[a->p.i]);
		a->p.i++;
	}
	if (!a->cmd && (a->p.candidate[0] == '>' || a->p.candidate[0] == '<'))
	{
		free(a->p.candidate);
		a->p.candidate = NULL;
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
	}
	add_candidate(a);
	a->p.i--;
}

void	parse_quote(t_all *a)
{
	if (a->p.candidate)
		add_candidate(a);
	a->p.start = a->p.i;
	if (a->line[a->p.i] == '\'')
		s_quote_process(a, a->line);
	else if (a->line[a->p.i] == '\"')
		d_quote_process(a, a->line);
	while (is_space(a->line[a->p.i]))
		a->p.i++;
	a->p.i--;
}

void	parse_one(t_all *a)
{
	int		size;

	add_candidate(a);
	size = ft_matrow(a->arg) - 1;
	if (size >= 0)
		process_env(a, a->arg[size]);
	a->p.i += 1;
	while (is_space(a->line[a->p.i]))
		a->p.i++;
	a->p.i--;
}

int		parse_last(t_all *a)
{
	int		size;

	if (!a->p.candidate)
		return (1);
	add_candidate(a);
	size = ft_matrow(a->arg) - 1;
	if (size >= 0)
		process_env(a, a->arg[size]);
	return (1);
}
