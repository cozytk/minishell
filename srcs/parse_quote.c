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

void	s_quote_process(t_all *a, char *line)
{
	char	*result;

	a->p.i++;
	result = NULL;
	while (line[a->p.i] != '\'')
	{
		if (!line[a->p.i])
		{
			ft_putstr_fd(" > ", 1);
			while (1)
			{
			}
		}
		if (line[a->p.i] == '\\')
			a->p.i++;
		result = ft_strcjoin(result, line[a->p.i]);
		a->p.i++;
	}
	a->p.i++;
	if (!a->cmd)
		a->cmd = result;
	else
		add_argument(a, result);
}

void	d_quote_process(t_all *a, char *line)
{
	char	*result;

	a->p.i++;
	result = NULL;
	while (line[a->p.i] != '\"')
	{
		if (!line[a->p.i])
		{
			ft_putstr_fd(" > ", 1);
			while (1)
			{
			}
		}
		if (line[a->p.i] == '\\')
			a->p.i++;
		result = ft_strcjoin(result, line[a->p.i]);
		a->p.i++;
	}
	a->p.i++;
	if (!a->cmd)
		a->cmd = result;
	else
		add_argument(a, result);
	process_env(a, result);
}
