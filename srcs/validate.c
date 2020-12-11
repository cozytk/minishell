#include "../inc/minishell.h"

int		has_identifier(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (ft_isdigit(*str))
		return (1);
	while (str[i])
	{
		if ((str[i] > 21 && str[i] < 48) || \
			(str[i] > 57 && str[i] < 65) || \
			(str[i] > 90 && str[i] < 97) || \
			(str[i] > 122 && str[i] < 127))
			return (1);
		i++;
	}
	return (0);
}

char	**check_identifier(char **mat)
{
	int i;

	i = -1;
	while (mat && mat[++i])
	{
		if (has_identifier(mat[i]))
		{
			if ((ft_strchr(mat[i], '=') || ft_strchr(mat[i], '$')) && \
				!(mat[i][0] == '=' || mat[i][0] == '$'))
				continue ;
			write_error("export", mat[i], ": not a valid identifier", 1);
			mat = ft_delete_row(mat, i);
			i = -1;
		}
	}
	return (mat);
}

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
