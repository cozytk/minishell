#include "../inc/minishell.h"

int main()
{
	char buf[1];
	struct stat st;
	int fd = open("Hello", O_CREAT|O_RDWR, 00777);
//	while (read(fd, buf, 1))
//		ft_putchar_fd('\0', fd);
//	ft_putchar_fd('\0', fd);
//	read(fd, buf, 1);
	stat("hello", &st);
	printf("%d\n", (int)st.st_size);
	return (0);
}