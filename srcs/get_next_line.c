/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:55:36 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/23 12:26:30 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

void	last_line(char **stack, char **line)
{
	if (*stack)
	{
		*line = ft_strdup(*stack);
		free(*stack);
		*stack = (void *)0;
	}
	else
		*line = ft_strdup("");
}

int		check_enter(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

int		reached_next_line(char **stack, char **line)
{
	int spot;

	if (!(spot = check_enter(*stack)))
		return (0);
	else
	{
		*line = ft_strdup_til_enter(*stack);
		after_enter(stack, spot);
		return (1);
	}
}

int		read_buff(int fd, char **stack, char **line)
{
	int		res;
	char	*temp;
	char	buff[BUFFER_SIZE + 1];

	while ((res = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[res] = 0;
		if (!(temp = gnl_strjoin(*stack, buff))
				|| !(*stack = ft_strdup(temp)))
			return (-1);
		free(temp);
		temp = (void *)0;
		if (res < BUFFER_SIZE && !(check_enter(*stack)))
			break ;
		if ((res = reached_next_line(stack, line)))
			return (res);
	}
	if (res >= 0)
	{
		last_line(stack, line);
		res = 0;
	}
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char		*stack[1025];
	int				res;

	if (fd < 0 || (read(fd, stack[fd], 0) < 0) ||
			BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	if (stack[fd] && (res = reached_next_line(&stack[fd], line)))
		return (res);
	res = read_buff(fd, &stack[fd], line);
	return (res);
}
