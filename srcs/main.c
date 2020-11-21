#include "../inc/minishell.h"
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *cmd;
	char *line;
	char **lines;
	char *tmp;
	int gnl;
	int state;
	pid_t pid;
	pid_t waitpid;
	write(1, "bash-3.2$ ", strlen("bash-3.2$ "));
	while ((gnl = get_next_line(0, &line)) > 0)
	{
			pid = fork();
			waitpid = wait(&state);
			if (pid < 0)
			{
				printf("%s\n", strerror(errno));
				exit(0);
			} else if (pid == 0)
			{
				tmp = strtok(line, " ");
				cmd = ft_strjoin("/bin/", tmp);
				free(tmp);
				lines = ft_split(line, ' ');
				execve(cmd, lines, envp);
				for (int i = 0; lines[i]; i++)
					free(lines[i]);
				free(lines);
//				write(1, "bash-3.2$ ", strlen("bash-3.2$ "));
				exit(0);
			}
			else if (pid > 0)
				write(1, "bash-3.2$ ", strlen("bash-3.2$ "));
	}
	printf("GNL return : %d | line : %s\n", gnl, line);
	free(line);
	return 0;
}

