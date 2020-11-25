#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int fd[2];
//	int state;
	char buff[20];
	if (pipe(fd) == -1)
	{
		printf("pipe error\n");
		exit(1);
	}
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	else if (pid == 0)
	{
		write(fd[1], "Hello\n", 6);
		usleep(10);
		read(fd[0], buff, 20);
		printf("%s", buff);
		exit(0);
	}
	else if (pid > 0)
	{
		read(fd[0], buff, 20);
		write(fd[1], "Bye\n", 20);
		printf("%s", buff);
	}
	return (0);
}








































//#include <unistd.h>
//#include <stdlib.h>
//
//int main(void)
//{
//	int fd[2];
////	int state;
//	char buff[12];
//	if (pipe(fd) == -1)
//		exit(1);
//
//	pid_t pid = fork();
//	if (pid > 0)
//	{
////		wait(&state);
//		read(fd[0], buff, 12);
//		write(1, buff, 12);
//	}
//	else if (pid == 0)
//	{
//		write(fd[1], "Hello World\n", 12);
//		exit(0);
//	}
//	else if (pid == -1)
//		exit(1);
//	return (0);
//}
////
//// Created by Taekyun Kim on 11/23/20.
////
//
