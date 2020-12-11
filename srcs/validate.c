/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:10:58 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/11 18:10:59 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*validate2(t_all *a, char *message)
{
	char	*temp;
	int		i;

	if (is_pipe_or_scolon(a->cmd[0]))
		message = ft_strcjoin(message, a->cmd[0]);
	else if (a->cmd && a->arg)
	{
		i = 0;
		while (a->arg[0][i] && is_sep_char(a->arg[0][i]))
		{
			message = ft_strcjoin(message, a->arg[0][i]);
			i++;
		}
	}
	else if (a->cmd)
	{
		temp = message;
		message = ft_strjoin(message, "newline");
		free(temp);
	}
	return (message);
}

int		validate(t_all *a)
{
	char	*message;

	if (!a->cmd)
		return (0);
	if (!(is_sep_char(a->cmd[0]) || is_pipe_or_scolon(a->cmd[0])))
		return (1);
	message = ft_strdup("bash: syntax error near unexpected token `");
	message = validate2(a, message);
	message = ft_strcjoin(message, '\'');
	ft_putendl_fd(message, 1);
	free(message);
	g_end = 258;
	return (0);
}
