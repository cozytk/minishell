#include "../inc/minishell.h"

int main()
{
	char buf[100];
	int fd[2];
	int fd_temp;
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		write(fd[1], "Hello World\n", 12);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, 0);
		fd_temp = dup(fd[0]);
		read(fd_temp, buf, 100);
	}
	printf("buf is %s", buf);
}

//
// Created by Taekyun Kim on 03/12/2020.
//

