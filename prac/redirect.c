#include "../../inc/minishell.h"

void	bash_error(char *cmd, char *msg, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
	exit(exit_code);
}

int exec_redirect(t_all *a, int opt, int fileno)
{
	int fd;

	if (fileno == STDIN_FILENO && ((stat(a->argv[i + 1] == -1)))) bash_error(a->argv[i + 1], " : No such file or directory", 1);
	fd = open(mat[i + 1], opt, 00777);
	/*
	 * if (other redirect)
	 * {
	 * 		close(fd);
	 * 		redirect(a);
	 * }
	 */
	dup2(fd, fileno);
	execve(a->cmd, a->argv, envp);
	close(fd);
	return (1);
}

int redirect(t_all *a)
{
	int i;

	i = 0;
	while (a->argv[i])
	{
		if (cmd_itself(">", a->argv[i]))
		{
			exec_redirect(a, O_WRONLY | O_CREAT | O_TRUNC, 1);
			return (1);
		}
		else if (cmd_itself(">>", a->argv[i]))
		{
			exec_redirect(a, O_WRONLY | O_CREAT | O_APPEND, 1);
			return (1);
		}
		else if (cmd_itself("<", a->argv[i]))
		{
			exec_redirect(a, O_RDONLY, 0);
			return (1);
		}
		i++;
	}
	return (0);
}