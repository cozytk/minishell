#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//void swap(char ***env, int i, int j)
//{ //	char *temp; //
//	temp = strdup(*env[i]);
//	printf("temp is %s\n", temp);
//	free(*env[i]);
//	*env[i] = strdup(*env[j]);
//	free(*env[j]);
//	*env[j] = strdup(temp);
//	free(temp);
//	sleep(3);
//}
//

typedef struct		s_all
{
	char **env;
}					t_all;

void swap_str(char **s1, char **s2)
{
	char *temp;

	temp = strdup(*s1);
	free(*s1);
	*s1 = strdup(*s2);
	free(*s2);
	*s2 = strdup(temp);
	free(temp);
}

void sort_mat(char ***env)
{
	int		i;
	int 	j;

	i = -1;
	while ((*env)[++i])
	{
		j = i;
		while ((*env)[++j])
		{
			if (strcmp((*env)[i], (*env)[j]) < 0)
				continue ;
			else if (strcmp((*env)[i], (*env)[j]) > 0)
				swap_str(&(*env)[i], &(*env)[j]);
			else
				exit(1);
		}
	}
}

void init_env(char **env, t_all *a)
{
	int row = 0;

	while (env[row])
		row++;
	a->env = malloc(sizeof(char *) * row);
	for (int i = 0; i < row; i++)
		a->env[i] = strdup(env[i]);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all a;
	(void)argc;
	(void)argv;

//	for (int i = 0; envp[i]; i++)
//		printf("%s\n", envp[i]);

	init_env(envp, &a);
	for (int i = 0; a.env[i]; i++)
		printf("%s\n", a.env[i]);
	printf("------------------\n");
	sort_mat(&a.env);
	for (int i = 0; a.env[i]; i++)
		printf("%s\n", a.env[i]);
//	printf("%p\n", env);
//	printf("%p\n", env[0]);
//	printf("%p\n", env[1]);
	return (0);
}


//
// Created by Taekyun Kim on 11/25/20.
//


