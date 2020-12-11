/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:44:58 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/08 23:45:40 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	s_quote_process(t_all *a)
{
	a->p.i++;
	while (a->line[a->p.i] != '\'')
	{
		if (!a->line[a->p.i])
		{
			ft_putstr_fd(" > ", 1);
			while (1)
			{
			}
		}
		if (a->line[a->p.i] == '\\' && !ft_isdigit(a->line[a->p.i + 1]))
			a->p.i++;
		a->p.candidate = ft_strcjoin(a->p.candidate, a->line[a->p.i]);
		a->p.i++;
	}
	a->p.i++;
	add_candidate(a);
}

void	d_quote_process(t_all *a)
{
	char	*env_processed;

	a->p.i++;
	while (a->line[a->p.i] != '\"')
	{
		if (!a->line[a->p.i])
		{
			ft_putstr_fd(" > ", 1);
			while (1)
			{
			}
		}
		if (a->line[a->p.i] == '\\' && !ft_isdigit(a->line[a->p.i + 1]))
			a->p.i++;
		a->p.candidate = ft_strcjoin(a->p.candidate, a->line[a->p.i]);
		a->p.i++;
	}
	a->p.i++;
	env_processed = process_env(a, a->p.candidate);
	if (a->p.candidate)
		free(a->p.candidate);
	a->p.candidate = env_processed;
	add_candidate(a);
}

void	quote_join2(t_all *a, int size)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	if (a->line[a->p.start - 1] != ' ' && size == 1)
	{
		temp = a->cmd;
		a->cmd = ft_strjoin(a->cmd, a->arg[0]);
		free(temp);
		a->arg = ft_delete_row(a->arg, 0);
	}
	else if (a->line[a->p.start - 1] != ' ' && size > 1)
	{
		temp = a->arg[size - 2];
		temp2 = a->arg[size - 1];
		temp3 = ft_strjoin(temp, temp2);
		a->arg = ft_delete_row(a->arg, size - 2);
		a->arg = ft_delete_row(a->arg, size - 1);
		add_argument(a, temp3);
	}
}

void	quote_join(t_all *a)
{
	int		size;

	if (!a->arg)
		return ;
	if (!(is_quote(a->line[a->p.start - 1])
				|| is_quote(a->line[a->p.start])))
		return ;
	size = ft_matrow(a->arg);
	if (a->p.start > 0 && a->cmd)
		quote_join2(a, size);
}
