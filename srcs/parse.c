#include "../inc/minishell.h"

int		is_sep_char(char c)
{
	if (c == '>' || c == ';' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		chk_only_space(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	add_argument(t_all *a, char *arg)
{
	int		argsize;
	int		i;
	char	**new_mat;

	if (chk_only_space(arg))
		return ;
	argsize = ft_matrow(a->arguments);
	new_mat = malloc(sizeof(char *) * (argsize + 2));
	i = 0;
	if (a->arguments)
	{
		while (a->arguments[i])
		{
			new_mat[i] = ft_strdup(a->arguments[i]);
			i++;
		}
		ft_free_mat(a->arguments);
	}
	new_mat[i] = arg;
	new_mat[i + 1] = NULL;
	a->arguments = new_mat;
}

int		is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int     parsing(t_all *a, char *line)
{
	int		i;
	int		count;
	int		start;
	char	*temp;

	i = 0;
	count = 0;
	start = 0;
	while (line[i])
	{
		if (is_sep_char(line[i]) || is_space(line[i]))
		{
			//temp = ft_substr(line, start, count);
			//printf("split : %s\n", temp);
			if (!a->command)
				a->command = ft_substr(line, start, count);
			else
				add_argument(a, ft_substr(line, start, count));
			if (is_sep_char(line[i]))
			{
				add_argument(a, ft_substr(line, start, 1));
				count = 1;
				i++;
			}
			start += count;
			count = 0;
			while (is_space(line[i]))
			{
				i++;
				start++;
			}
			continue;
		}
		count++;
		i++;
	}
	temp = ft_substr(line, start, count);
	if (line[i - 1] != ' ')
		add_argument(a, temp);
	else
		free(temp);
	//printf("split : %s\n", temp);
}

void	show_com(t_all *a)
{
	//printf("%s\n", a->command);
	if (!a->command)
		return ;
	write(1, a->command, ft_strlen(a->command));
	write(1, &"\n", 1);
}

void	show_arg(t_all *a)
{
	int		i;

	i = 0;
	if (!a->arguments)
		return ;
	while (a->arguments[i])
	{
		write(1, a->arguments[i], ft_strlen(a->arguments[i]));
	write(1, &"\n", 1);
		i++;
	}
}

void    init(t_all *a)
{
    a->command = NULL;
    a->arguments = NULL;
}

int		main(void)
{
	t_all	*a;
	char	*line;

	a = malloc(sizeof(t_all) * 1);
    init(a);
	while (1)
	{
		get_next_line(0, &line);
		parsing(a, line);
		//printf("aadsfsaf%s\n", a->command);
		show_com(a);
		show_arg(a);
		free(a->command);
		a->command = NULL;
		free(line);
	}
}
