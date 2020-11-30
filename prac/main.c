#include <stdio.h>
#include <stdlib.h>
#include "../inc/minishell.h"

void f(char *s)
{
	s="bye";
	printf("%p\n", s);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)(argc || argv || envp);
	char *s = "Hello";
	printf("%p\n", s);
	f(s);
	printf("%s\n", s);
}
