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
	char *tmp;
	char *ret;

	if (!(str || *str))
		return (0);
	while (*str + i)
	{
		if (*(*str + i) == ' ')
			break ;
		i++;
	}
	ret = strndup(*str, i);
	tmp = *str;
	if (i < (int)(strlen(*str)))
		*str = strdup(*str + i + 1);
	else
		*str = strdup("");
	free(tmp);
	return (ret);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *line;
	char init_str[20] = {"bash-3.2$ "};
	char *cmd;
//	int fd = open("test", O_RDONLY);

	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	ft_write(init_str);
	while (get_next_line(0, &line) > 0)
	{
		// | ; > " '
		// remove ' ' before string
		cmd = get_cmd(&line);
		printf("cmd is %s, line is %s\n", cmd, line);
		if (!strcmp(cmd, "exit"))
			exit(0);
		free(cmd);
		free(line);
		ft_write(init_str);
	}
	printf("%s\n", line);
	free(line);
	return (0);
}
