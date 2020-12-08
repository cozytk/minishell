/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:25:55 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/04 22:06:45 by taehkim          ###   ########.fr       */
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

void	add_parsed(t_all *a, char *line)
{
	char	*temp;

	temp = ft_substr(line, a->p.start, a->p.count);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return ;
	}
	if (!a->cmd)
		a->cmd = temp;
	else
		add_argument(a, temp);
}

void	parse_backslash(t_all *a)
{
	add_parsed(a, a->line);
	a->p.start += a->p.count;
	a->p.count = 2;
	add_parsed(a, a->line);
	a->p.count = -1;
	a->p.i += 2;
	a->p.start = a->p.i;
	a->p.i--;
}

int		parsing(t_all *a)
{
	while (is_space(a->line[a->p.i]))
		a->p.i++;
	parse_init(a);
	while (a->line[a->p.i])
	{
		if (a->line[a->p.i] == '\\' && a->line[a->p.i - 1] != '\\')
			parse_backslash(a);
		if (is_pipe_or_scolon(a->line[a->p.i]) && a->cmd)
			return (parse_pipe_scolon(a));
		else if (is_sep_char(a->line[a->p.i]))
			parse_redirect(a);
		else if (is_quote(a->line[a->p.i]))
			parse_quote(a);
		else if (is_space(a->line[a->p.i]))
			parse_one(a);
		else if (a->line[a->p.i + 1] == '\0')
			return (parse_last(a));
		a->p.count++;
		a->p.i++;
	}
	return (1);
}
