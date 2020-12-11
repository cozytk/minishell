/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:50:53 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/11 20:56:37 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	run_cmd(t_all *a, int flag)
{
	if (flag)
		dup2(a->fd[1], STDOUT_FILENO);
	else
		dup2(a->fd[0], STDIN_FILENO);
	close(a->fd[0]);
	close(a->fd[1]);
	if (flag)
	{
		redirect(a);
		if (!(cmd_builtin(a) || cmd_exec(a)))
		{
			free_com_arg(a);
			exit(0);
		}
		exit(1);
	}
	else
	{
		free_com_arg(a);
		main_loop(a);
		free_com_arg(a);
		exit(0);
	}
}

int		ft_pipe(t_all *a)
{
	pid_t pid;
	pid_t pid2;

	if (pipe(a->fd) == -1)
		bash_cmd_error("pipe", "pipe < 0", 1);
	pid = fork();
	if (pid < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	else if (pid == 0)
		run_cmd(a, 1);
	pid2 = fork();
	if (pid2 < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	else if (pid2 == 0)
		run_cmd(a, 0);
	close(a->fd[0]);
	close(a->fd[1]);
	waitpid(pid2, 0, 0);
	return (0);
}
