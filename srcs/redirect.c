/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:39:27 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/11 20:39:28 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bash_error(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_end = 1;
}

int		exec_redirect(t_all *a, int i, int opt, int fileno)
{
	int			file_fd;
	struct stat	st;

	a->fileno = fileno;
	a->arg = ft_delete_row(a->arg, i);
	if (fileno == STDIN_FILENO && (stat(a->arg[i], &st) == -1))
	{
		bash_error(a->arg[i]);
		free_com_arg(a);
		return (0);
	}
	file_fd = open(a->arg[i], opt, 00777);
	a->arg = ft_delete_row(a->arg, i);
	if (redirect(a))
	{
		close(file_fd);
		return (0);
	}
	a->redirect = 1;
	a->fd_tmp = dup(a->fileno);
	dup2(file_fd, a->fileno);
	return (1);
}

int		redirect(t_all *a)
{
	int			i;

	i = 0;
	if (!a->arg)
		return (0);
	while (a->arg[i])
	{
		if (cmd_itself(">", a->arg[i]))
		{
			exec_redirect(a, i, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
			return (1);
		}
		else if (cmd_itself(">>", a->arg[i]))
		{
			exec_redirect(a, i, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
			return (1);
		}
		else if (cmd_itself("<", a->arg[i]))
		{
			exec_redirect(a, i, O_RDONLY, STDIN_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
