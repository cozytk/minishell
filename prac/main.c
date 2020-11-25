#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ft_realloc(char **temp)
{
	free(*temp);
	*temp = NULL;
}

int main(void)
{
	char *temp = malloc(20);

	for (int i = 0; i < 20; i++)
		temp[i] = 'a';
	temp[20] = '\0';
	printf("%p\n", temp);
	puts(temp);
	ft_realloc(&temp);
	printf("%p\n", temp);
	puts(temp);
	return (0);
}
//
// Created by Taekyun Kim on 11/25/20.
//

