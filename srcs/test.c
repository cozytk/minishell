#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pid;
	if ((pid=fork()) == 0)
	{
		sleep(1);
		printf("[child process %d] created from %d\n", getpid(), getppid());
		exit(0);
	}
	printf("[parent process %d] create %d process, ppid:%d\n", getpid(),pid,getppid());
}
//
// Created by Taekyun Kim on 21/11/2020.
//

