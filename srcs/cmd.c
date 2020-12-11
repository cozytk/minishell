/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <taekkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 20:32:59 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/12 04:31:23 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_exec_err(t_all *a, int flag)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(a->cmd, 2);
	if (!flag)
		ft_putendl_fd(": command not found", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
	exit(127);
}

void	run_execve(t_all *a, char **arg)
{
	int		i;
	char	**mat;
	char	*cmd;
	char	*path;

	if (a->cmd[0] == '/')
		execve(a->cmd, arg, a->env);
	else if ((i = find_row(a->env, "PATH=")) != -1)
	{
		mat = ft_split(a->env[i] + 5, ':');
		cmd = ft_strjoin("/", a->cmd);
		i = -1;
		while (mat[++i])
		{
			path = ft_strjoin(mat[i], cmd);
			execve(path, arg, a->env);
			free(path);
		}
		free(cmd);
		ft_free_mat(mat);
		write_exec_err(a, 0);
	}
	write_exec_err(a, 1);
}

int		cmd_exec(t_all *a)
{
	char	**lines;
	int		state;
	pid_t	pid;

	if (g_end != -1 || !a->cmd)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		lines = ft_matadd_front(a);
		run_execve(a, lines);
		ft_free_mat(lines);
	}
	else if (pid == -1)
		exit(1);
	if (pid > 0)
	{
		waitpid(pid, &state, 0);
		if (!WIFSIGNALED(state))
			g_end = WEXITSTATUS(state);
	}
	return (0);
}

int		cmd_builtin(t_all *a)
{
	if (!a->cmd)
		return (0);
	if (ft_exit(a))
		return (1);
	if (export(a) || cd(a) || pwd(a) || env(a) || unset(a) || echo(a))
	{
		if (g_end == -1)
		{
			g_end = 0;
			return (1);
		}
	}
	return (0);
}
