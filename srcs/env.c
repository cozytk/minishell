#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	for (int i = 0; envp[i]; i++)
		printf("%s, %lu\n", envp[i], sizeof(envp[i]));
	return (0);
}
//
// Created by Taekyun Kim on 11/23/20.
//

