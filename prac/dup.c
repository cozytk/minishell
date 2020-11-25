#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("test", O_RDWR);

	printf("%d\n", fd);
	return (0);
}
