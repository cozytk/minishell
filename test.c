#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *s1 = malloc(20);
	char *s2 = malloc(20);
	char *tmp;

	s1 = "Hello World\n";
	s2 = "Bye World\n";
	tmp = s1;
	s1 = s2;
	free(tmp);
	printf ("%s", s1);
	return (0);
}

//char *func(char **str)
//{
//	int i = 0;
//	char *tmp;
//
//	if (!(str || *str))
//		return (0);
//	while (*str)
//	{
//		if (*(*str + i) == ' ')
//		{
//			tmp = *str;
//			*str += i;
//			free(tmp);
//		}
//		i++;
//	}
//
//	printf("%c\n", *(*str + 1));
//	printf("%c\n", (*str + 1)[0]);
//	printf("%s\n", *str + 1);
//	return (strdup(*str));
//}

//char *f2(char *str)
//{
//	char *s1 = malloc(20);
//
//	s1 = "Bye World\n";
////	free(str);
////	str = 0;
//	str = s1;
//	return (str);
//}
//
//int main()
//{
//	char *str = (char *)malloc(20);
//	char *temp;
//
//	str = "Hello World\n";
//	char *tmp = str;
//	temp = f2(str);
//	free(tmp);
//	printf("str is %s %p, temp is %s %p\n", str, str, temp, temp);
////	printf("str is %s %p, temp is %s %p, tmp is %s %p\n", str, str, temp, temp, tmp, tmp);
//	while (1)
//		;
//	return (0);
//}
//
// Created by Taekyun Kim on 23/11/2020.
//

