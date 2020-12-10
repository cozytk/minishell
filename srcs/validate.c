#include "../inc/minishell.h"

int		validate(t_all *a)
{
	char	*temp;
	char	*message;
	int		i;

	if (!a->cmd)
		return (0);
	if (!(is_sep_char(a->cmd[0]) || is_pipe_or_scolon(a->cmd[0])))
		return (1);
	message = ft_strdup("bash: syntax error near unexpected token `");
	if (is_pipe_or_scolon(a->cmd[0]))
		message = ft_strcjoin(message, a->cmd[0]);
	else if (a->cmd && a->arg)
	{
		i = 0;
		while (a->arg[0][i] && is_sep_char(a->arg[0][i]))
		{
			message = ft_strcjoin(message, a->arg[0][i]);
			i++;
		}
	}
	else if (a->cmd)
	{
		temp = message;
		message = ft_strjoin(message, "newline");
		free(temp);
	}
	message = ft_strcjoin(message, '\'');
	ft_putendl_fd(message, 1);
	free(message);
	g_end = 258;
	return (0);
}
