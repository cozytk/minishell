/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:08:53 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/30 20:08:54 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>

void sig_handle(int signo)
{
	if (signo == SIGINT)
		ft_write("\nbash-3.2$ ");
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

int 	cmd_exec(char *line, t_all *a)
{
	char **lines;
	char *cmd;
	char *path_cmd;
	char *path_cmd2;
	int state;
	pid_t pid;

	cmd = get_cmd(line);
	pid = fork();
	if (pid == 0)
	{
		path_cmd = ft_strjoin("/bin/", cmd);
		path_cmd2 = ft_strjoin("/usr/bin/", cmd);
		lines = ft_split(line, ' ');
		if ((execve(path_cmd, lines, a->env) == -1) &&
			execve(path_cmd2, lines, a->env) == -1)
		{
			ft_putstr_fd("bash: command not found: ", 2);
			ft_putendl_fd(cmd, 2);
		}
		exit(1);
//		free(cmd);
//		free(path_cmd);
//		free(path_cmd2);
//		free(lines);
//		free(line);
	}
	else if (pid > 0)
	{
		waitpid(pid, &state, 0);
		free(cmd);
		free(line);
	}
	else if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	return (1);
}

int		cmd_builtin(char *line, t_all *a)
{
	if (!ft_strncmp("exit", line, 4))
		exit(1);
	if (echo(line))
		return (1);
	else if (cd(line, a))
		return (1);
	else if (pwd(line))
		return (1);
	else if (env(line, a))
		return (1);
	else if (unset(line, a))
		return (1);
	else if (export(line, a))
		return (1);
	return (0);
}


int main(int argc, char *argv[], char *envp[])
{
	t_all a;
	char *line;
	(void)argc;
	(void)argv;

	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	init_env(envp, &a);
	init_export(&a, a.env);
	while (ft_write(INIT) && get_next_line(0, &line) > 0)
	{
		if (*line == '\0')
		{
			line = (void *)0;
			free(line);
			continue;
		}
		if (cmd_builtin(line, &a))
			continue ;
		if (cmd_exec(line, &a))
			continue ;
		line = (void *)0;
	}
	return (0);
}

