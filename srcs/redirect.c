#include "../inc/minishell.h"

void 	reset_fd(t_all *a)
{
	dup2(a->fd_redirect[ORIG], a->fd_redirect[COPY]);
	close(a->fd_redirect[ORIG]);
	close(a->fd_redirect[COPY]);
}

void	bash_error(char *cmd, char *msg, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
	exit(exit_code);
}

int exec_redirect(t_all *a, int i, int opt, int fileno)
{
	a->arg = ft_delete_row(a->arg, i);
	if (fileno == STDIN_FILENO && (stat(a->arg[i], 0) == -1))
		bash_error(a->arg[i], " : No such file or directory", 1);
	a->fd_redirect[ORIG] = open(a->arg[i], opt, 00777);
	a->arg = ft_delete_row(a->arg, i);
	if (redirect(a))
	{
		close(a->fd_redirect[ORIG]);
		return (0);
	}
	a->redirect = 1;
	a->fd_redirect[COPY] = dup(a->fd_redirect[ORIG]);
	dup2(a->fd_redirect[ORIG], fileno);
	return (1);
}

int redirect(t_all *a)
{
	int i;

	i = 0;
	if (!a->arg)
		return (0);
	while (a->arg[i])
	{
		if (cmd_itself(">", a->arg[i]))
		{
			exec_redirect(a, i, O_WRONLY | O_CREAT | O_TRUNC, 1);
			return (1);
		}
		else if (cmd_itself(">>", a->arg[i]))
		{
			exec_redirect(a, i, O_WRONLY | O_CREAT | O_APPEND, 1);
			return (1);
		}
		else if (cmd_itself("<", a->arg[i]))
		{
			exec_redirect(a, i, O_RDONLY, 0);
			return (1);
		}
		i++;
	}
	return (0);
}
