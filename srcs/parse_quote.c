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
	quote_join(a);
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
	{
		add_argument(a, result);
		process_env(a, result);
	}
	quote_join(a);
}

void	quote_join(t_all *a)
{
	//cmd 있고 arg 하나 -> 만약 붙어있다? 합치고 cmd 갱신, arg 제거 arg NULL 처리는 밖에서(안해줘도 될듯)
	//cmd 만 있 -> return ;
	//cmd 있고 arg 여러개
	int		size;
	char	*temp;
	char	*temp2;
	char	*temp3;

	if (!a->arg)
		return ;
	if (!(is_quote(a->line[a->p.start - 1])
				|| is_quote(a->line[a->p.start])))
		return ;
	size = ft_matrow(a->arg);
	if (a->p.start > 0 && a->cmd)
	{
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
}
