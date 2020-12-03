#include "../inc/minishell.h"

int 	ft_pipe(t_all *a)
{
	int fd = open("hello", O_RDWR|O_CREAT, 00777);
	int fd1;
	/*pid_t pid;

	if (pipe(a->fd) == -1)
		bash_cmd_error("pipe", "pipe < 0", 1);
	pid = fork();
	if (pid < 0)
		bash_cmd_error("pid", "pid < 0", 1);*/
	fd1 = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	export("export", a);
	dup2()
	dup2(fd, STDIN_FILENO);
	execve("/bin/cat", a->arg, a->env);
	close(fd);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all a;
}
