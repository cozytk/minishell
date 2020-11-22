#include "../inc/minishell.h"
#include <string.h>

void ft_write(char *str)
{
	write(1, str, strlen(str));
}

void sig_handle(int signo)
{
	if (signo == SIGINT)
		ft_write("\nbash-3.2$ ");
}

char	*get_cmd(char **str)
{
	int i = 0;

	if (!(str || *str))
		return (0);
	while (*str[i])
	{
		if (*str[i] && *str[i] == ' ')
		{
			*str += i;
			return (strndup(*str, i));
		}
		i++;
	}
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *line;
	char init_str[20] = {"bash-3.2$ "};
	char *cmd;

	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	ft_write(init_str);
	while (get_next_line(0, &line) > 0)
	{
		// | ; > " '
		// remove ' ' before string
		cmd = get_cmd(&line);
		printf("cmd is %s, line is %s\n", cmd, line);
		printf("%s\n", line);
		free(line);
		write(1, init_str, strlen(init_str));
	}
	printf("line is %s\n", line);
	free(line);
	return (0);
}
