/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:08:53 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/04 20:45:37 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>

int		update_end(t_all *a)
{
	if (!ft_strncmp(a->cmd, "$?", 2))
	{
		ft_putnbr_fd(a->end, 2);
		ft_putendl_fd(": command not found", 2);
		a->end = 127;
		return (0);
	}
	a->end = -1;
	return (1);
}

void sig_handle(int signo)
{
	int state;
	int res;

	if ((res = wait(&state)) > 0)
	{
		if (signo == SIGINT)
		{
			ft_putchar_fd('\n', 1);
//			a->end = 130;
		}
		else if (signo == SIGQUIT)
		{
			ft_putendl_fd("Quit", 1);
//			a->end = 131;
		}
		return;
	}
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(INIT, 1);
//		a->end = 130;
	}
	else if (signo == SIGQUIT)
	{
		ft_putchar_fd(8, 1);
		ft_putchar_fd(8, 1);
		ft_putchar_fd(' ', 1);
		ft_putchar_fd(' ', 1);
		ft_putchar_fd(8, 1);
		ft_putchar_fd(8, 1);
		//ft_putchar_fd('\n', 1);
		//ft_putstr_fd(INIT, 1);
//		a->end = 127;
	}
}

char	*get_cmd(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	if (i > 0)
		return (strndup(str, i));
	return (ft_strdup(""));
}

void	run_execve(t_all *a, char **arg)
{
	int		i;
	char	**mat;
	char	*cmd;
	char 	*path;

	i = find_row(a->env, "PATH=");
	mat = ft_split(a->env[i] + 5, ':');
	cmd = ft_strjoin("/", a->cmd);
	i = 0;
	while (mat[i])
	{
		path = ft_strjoin(mat[i], cmd);
		execve(path, arg, a->env);
		free(path);
		i++;
	}
	ft_putstr_fd(a->cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free(cmd);
	ft_free_mat(mat);
	exit(127);
}

int		pipe_scolon_alone(t_all *a)
{
	if (a->cmd[0] == '|' || a->cmd[0] == ';')
	{
		if (a->cmd[0] == '|')
			ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		else if (a->cmd[0] == ';')
			ft_putendl_fd("bash: syntax error near unexpected token `;'", 2);
		return (1);
	}
	return (0);
}

int 	cmd_exec(t_all *a)
{
	char **lines;
	char **tmp;
	pid_t pid;

	if (a->end != -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		tmp = malloc(sizeof(char *) * 2);
		tmp[0] = ft_strdup(a->cmd);
		tmp[1] = (void *)0;
		lines = ft_matjoin(tmp, a->arg);
		run_execve(a, lines);
		ft_free_mat(tmp);
		ft_free_mat(lines);
		exit(127);
	}
	else if (pid == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	waitpid(pid, 0, 0);
	return (0);
}

int     cmd_builtin(t_all *a)
{
	ft_exit(a);
    if (export(a) || cd(a) || pwd(a) || env(a) || unset(a) || echo(a))
	{
    	if (a->end == -1)
		{
			a->end = 0;
			return (1);
		}
	}
    return (0);
}

void 	update_pwd(t_all *a)
{
	char tmp[1024];
	int i;
	int j;

	if (!a->cd)
		return;
	i = find_row(a->env, "OLDPWD");
	j = find_row(a->env, "PWD");
	ft_free(a->env[i]);
	a->env[i] = ft_strjoin("OLD", a->env[j]);
	ft_free(a->env[j]);
	getcwd(tmp, 1024);
	a->env[j] = ft_strjoin("PWD=", tmp);
	a->cd = 0;
}

int 	main_loop(t_all *a)
{
	parsing(a);
	if (!update_end(a))
		return (0);
	if (!a->cmd)
		return (-1);
	if (pipe_scolon_alone(a))
		return (0);
	init_export(a, a->env);
	if (a->p.pipe)
	{
		ft_pipe(a);
		return (a->end);
	}
	update_pwd(a);
	redirect(a);
	cmd_builtin(a);
	cmd_exec(a);
	if (a->p.s_colon)
	{
		free_com_arg(a);
		main_loop(a);
	}
	return (a->end);
}

void 	init_struct(t_all *a)
{
	a->end = -1;
	a->cd = 0;
	a->fd_tmp = 0;
	a->redirect = 0;
	a->fileno = 0;
	a->cmd = 0;
	a->line = 0;
	a->env = 0;
	a->ept = 0;
	a->init_home = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	t_all *a;
	char *tmp;
	(void)argc;
	(void)argv;

	a = malloc(sizeof(t_all));
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	init_struct(a);
	init_env(envp, a);
	while (ft_write(INIT) && get_next_line(0, &(a->line)) > 0)
	{
		if (!a->line[0])
		{
			ft_free(a->line);
			a->end = 127;
			continue;
		}
		tmp = a->line;
		init(a);
		init_index(a);
		main_loop(a);
		free_com_arg(a);
		if (a->redirect)
			dup2(a->fd_tmp, a->fileno);
		free(tmp);
		tmp = (void *)0;
	}
	return (0);
}
