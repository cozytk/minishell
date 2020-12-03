#include "../inc/minishell.h"

int 	ft_pipe(t_all *a)
{
	pid_t pid;
	pid_t pid2;

	if (pipe(a->fd) == -1)
		bash_cmd_error("pipe", "pipe < 0", 1);
	pid = fork();
	if (pid < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	else if (pid == 0)
	{
		dup2(a->fd[1], STDOUT_FILENO);
		close(a->fd[0]);
		close(a->fd[1]);
		redirect(a);
		cmd_builtin(a);
		cmd_exec(a);
		exit(0);
	}
	pid2 = fork();
	if (pid2 < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	else if (pid2 == 0)
	{
		dup2(a->fd[1], STDIN_FILENO);
		main_loop(a);
		close(a->fd[0]);
		close(a->fd[1]);
		redirect(a);
		cmd_builtin(a);
		cmd_exec(a);
		exit(0);
	}
	close(a->fd[0]);
	close(a->fd[1]);
	return (0);
}
