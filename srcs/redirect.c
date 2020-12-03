#include "../inc/minishell.h"

void	bash_error(char *cmd, char *msg, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
	exit(exit_code);
}

int 	more_redirect(t_all *a, int i, int fd)
{
	char **tmp;

	tmp = ft_delete_row(a->arg, i);
	tmp = ft_delete_row(tmp, i + 1);
	if (redirect(a))
	{
		close(fd);
		ft_free_mat(a->arg);
		a->arg = (void *)0;
		a->arg = ft_matdup(tmp);
		ft_free_mat(tmp);
		return (1);
	}
	ft_free_mat(tmp);
	return (0);
}

int exec_redirect(t_all *a, int i, int opt, int fileno)
{
	int		fd;

	if (fileno == STDIN_FILENO && (stat(a->arg[i + 1], 0) == -1))
		bash_error(a->arg[i + 1], " : No such file or directory", 1);
	fd = open(a->arg[i + 1], opt, 00777);
	if (more_redirect(a, i, fd))
		return (0);
	close(fd);
//	a->fd_tmp = dup(fileno);
	dup2(fd, fileno);
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
