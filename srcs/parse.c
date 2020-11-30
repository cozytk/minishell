#include "../inc/minishell.h"

int		is_sep_char(char c)
{
	if (c == ' ' || c == '>' || c == ';' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	add_argument(t_all *a, char *arg)
{
	int		argsize;
	int		i;
	char	**new_mat;

	argsize = ft_matrow(a->arguments);
	new_mat = malloc(sizeof(char *) * (argsize + 2));
	i = 0;
	while (a->arguments[i])
	{
		new_mat[i] = ft_strdup(a->arguments[i]);
		i++;
	}
	new_mat[i] = arg;
	new_mat[i + 1] = NULL;
	ft_free_mat(a->arguments);
	a->arguments = new_mat;
}

int     parsing(t_all *a, char *line)
{
	int		i;
	int		count;
	int		start;

	i = 0;
	count = 0;
	start = 0;
	while (line[i])
	{
		//printf("%c\n", line[i]);
		if (is_sep_char(line[i]))
		{
			if (!a->command)
				a->command = ft_substr(line, start, count);
			/*
			else
				add_argument(a, ft_substr(line, start, count));
				*/
			start += count;
			count = 0;
			while (line[i] == ' ')
			{
				i++;
				start++;
			}
			continue;
		}
		count++;
		i++;
	}
}

void	show_com(t_all *a)
{
	//printf("%s\n", a->command);
	write(1, a->command, ft_strlen(a->command));
}

void	show_arg(t_all *a)
{
	int		i;

	i = 0;
	while (a->arguments[i])
	{
		write(1, a->arguments[i], ft_strlen(a->command));
		i++;
	}
}

int		main(void)
{
	t_all	*a;
	char	*line;

	a = malloc(sizeof(t_all) * 1);
	while (1)
	{
		get_next_line(0, &line);
		parsing(a, line);
		//printf("aadsfsaf%s\n", a->command);
		show_com(a);
		//show_arg(a);
		free(line);
	}
}
