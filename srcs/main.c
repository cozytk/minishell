/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:08:53 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/04 14:11:37 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>

void sig_handle(int signo, t_all *a)
{
	if (signo == SIGINT)
		ft_write("\nbash-3.2$ ");
	else if (signo == SIGQUIT)
	{
		a->
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
//		free(path);
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(a->cmd, 2);
	ft_putendl_fd(": command not found", 2);
//	free(cmd);
//	ft_free_mat(mat);
	exit(1);
}

int 	cmd_exec(t_all *a)
{
	char **lines;
	char **tmp;
	pid_t pid;

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
		exit(0);
	}
	else if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	waitpid(pid, 0, 0);
	return (1);
}

int     cmd_builtin(t_all *a)
{
	if (!(a->cmd))
		return (0);
	ft_exit(a);
    if (export(a) || cd(a) || pwd(a) || env(a) || unset(a) || echo(a))
	    return (1);
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
	// validate();
	if (a->p.pipe)
	{
		ft_pipe(a);
		return (0); //no more pipe
	}
	init_export(a, a->env);
	update_pwd(a);
	redirect(a);
	if (cmd_builtin(a) || cmd_exec(a))
		return (1);
	return (0);
}

void 	init_struct(t_all *a)
{
	a->cd = 0;
	a->fd_tmp = 0;
	a->redirect = 0;
	a->fileno = 0;
	a->cmd = 0;
	a->line = 0;
	a->homepath = 0;
	a->end = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	t_all *a;
	char *tmp;
	(void)argc;
	(void)argv;

	a = malloc(sizeof(t_all));
	if (signal(SIGINT, sig_handle))
		a->end = 130;
	if (signal(SIGQUIT, sig_handle))
		a->end = 131;
	init_struct(a);
	init_env(envp, a);
//	for (int i = 0; a->ept[i]; i++)
//		printf("%s\n", a->ept[i]);
	while (ft_write(INIT) && get_next_line(0, &(a->line)) > 0)
	{
		if (!a->line[0])
		{
			free(a->line);
			continue ;
		}
		tmp = a->line;
		init(a);
		init_index(a);
		main_loop(a);
		if (a->redirect)
			dup2(a->fd_tmp, a->fileno);
		free(tmp);
		tmp = (void *)0;
	}
	return (0);
}
//
//int main(int argc, char *argv[], char *envp[])
//{
//	t_all a;
//	(void)argc;
//	(void)argv;
//
//	signal(SIGINT, sig_handle);
//	signal(SIGQUIT, sig_handle);
//	init_env(envp, &a);
//	init_export(&a, a.env);
//	while (ft_write(INIT) && get_next_line(0, &a.line) > 0)
//	{
//		main_loop(&a);
//		if (a.redirect)
//       		dup2(a.fd_tmp, a.fileno);
//		free(a.line);
//		a.line = (void *)0;
//	}
//	return (0);
//}
//
