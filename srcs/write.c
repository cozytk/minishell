#include "../inc/minishell.h"

void	write_quote(char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != '=')
		ft_putchar_fd(str[i], 1);
	if (!ft_strrchr(str, '='))
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	ft_write("=\"");
	while (str[++i])
		ft_putchar_fd(str[i], 1);
	ft_write("\"\n");
}

int		write_error(char *cmd, char *str, char *err, int exit)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	ft_putendl_fd(err, 2);
	g_end = exit;
	return (g_end);
}

void	bash_cmd_error(char *cmd, char *msg, int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
	exit(exit_code);
}

void	ft_erase(void)
{
	ft_putchar_fd(8, 1);
	ft_putchar_fd(8, 1);
	ft_putchar_fd(' ', 1);
	ft_putchar_fd(' ', 1);
	ft_putchar_fd(8, 1);
	ft_putchar_fd(8, 1);
	g_end = 127;
}
