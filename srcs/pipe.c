#include <minishell.h>

int 	ft_pipe(t_all *a)
{
	pid_t pid;

	if (pipe(a->fd) == -1)
		bash_cmd_error("pipe", "pipe < 0", 1);
	pid = fork();
	if (pid < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	dup2(a->fd[1], STDOUT_FILENO);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all *a;

	(void)(argv||envp);
	pipe(a);
	return (0);
}
