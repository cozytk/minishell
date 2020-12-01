#include "../inc/minishell.h"

int		is_sep_char(char c)
{
	if (c == '>' || c == ';' || c == '<')
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
	{
		free(arg);
		return ;
	}
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
        free(a->arguments);
        a->arguments = NULL;
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

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	s_quote_process(t_all *a, char *line)
{
	int		start;

	a->p.count = 0;
	a->p.i++;
	start = a->p.i;
	while (line[a->p.i] != '\'')
	{
		if (line[a->p.i] == '\0')
		{
			write(1, "> ", 2);
			while (1);
		}
		a->p.count++;
		a->p.i++;
	}
	if (!a->command)
		a->command = ft_substr(line, start, a->p.count);
	else
		add_argument(a, ft_substr(line, start, a->p.count));
	a->p.i++;
}

void	d_quote_process(t_all *a, char *line)
{
	int		start;

	a->p.count = 0;
	a->p.i++;
	start = a->p.i;
	while (line[a->p.i] != '\"')
	{
		if (line[a->p.i] == '\0')
		{
			write(1, "> ", 2);
			while (1);
		}
		a->p.count++;
		a->p.i++;
	}
	if (!a->command)
		a->command = ft_substr(line, start, a->p.count);
	else
		add_argument(a, ft_substr(line, start, a->p.count));
	a->p.i++;
}

int		is_pipe_or_scolon(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

int     parsing(t_all *a, char *line)
{
	while (line[a->p.i] == ' ')
		a->p.i++;
	a->p.start = a->p.i;
	while (line[a->p.i])
	{
		if (is_pipe_or_scolon(line[a->p.i]))
		{
			if (line[a->p.i - 1] != ' ' && a->p.i > 1)
			{
				// 그 전에 꺼 집어넣고
				if (!a->command)
					a->command = ft_substr(line, a->p.start, a->p.count);
				else
					add_argument(a, ft_substr(line, a->p.start, a->p.count));
			}
			a->p.i++;
			a->p.start = a->p.i;
			a->p.count = 0;
			return (0);
		}
		else if (is_space(line[a->p.i]))
		{
			//temp = ft_substr(line, start, count);
			//printf("split : %s\n", temp);
			if (!a->command)
				a->command = ft_substr(line, a->p.start, a->p.count);
			else
				add_argument(a, ft_substr(line, a->p.start, a->p.count));
			a->p.start += a->p.count;
			a->p.count = 0;
			while (is_space(line[a->p.i]))
			{
				a->p.i++;
				a->p.start++;
			}
			continue;
		}
        else if (is_sep_char(line[a->p.i]))
        {
			if (line[a->p.i - 1] != ' ' && a->p.i > 1)
			{
				// 그 전에 꺼 집어넣고
				if (!a->command)
					a->command = ft_substr(line, a->p.start, a->p.count);
				else
					add_argument(a, ft_substr(line, a->p.start, a->p.count));
			}
			a->p.start = a->p.i;
            a->p.count = 1;
			if (line[a->p.i] == '>' && line[a->p.i + 1] == '>')
				a->p.count++;
			add_argument(a, ft_substr(line, a->p.start, a->p.count));
            a->p.i += a->p.count;
			a->p.start = a->p.i;
			a->p.count = 0;
			continue ;
        }
		else if (is_quote(line[a->p.i]))
		{
			if (line[a->p.i - 1] != ' ' && a->p.i > 1)
			{
				// 그 전에 꺼 집어넣고
				if (!a->command)
					a->command = ft_substr(line, a->p.start, a->p.count);
				else
					add_argument(a, ft_substr(line, a->p.start, a->p.count));
			}
			if (line[a->p.i] == '\'')
				s_quote_process(a, line);
			else if (line[a->p.i] == '\"')
				d_quote_process(a, line);
			a->p.start = a->p.i;
			while (is_space(line[a->p.i]))
			{
				a->p.i++;
				a->p.start++;
			}
			a->p.count = 0;
			continue ;
		}
		a->p.count++;
		a->p.i++;
	}
	//temp = ft_substr(line, start, count);
	if (line[a->p.i - 1] != ' ')
	{
		if (!a->command)
			a->command = ft_substr(line, a->p.start, a->p.count);
		else
			add_argument(a, ft_substr(line, a->p.start, a->p.count));
	}
	return (1);
	//printf("split : %s\n", temp);
	//env_interpret(a);
}

void	show_com(t_all *a)
{
    write(1, &"==========command==========\n", 28);
	if (!a->command)
		return ;
	write(1, a->command, ft_strlen(a->command));
	write(1, &"\n", 1);
}

void	show_arg(t_all *a)
{
	int		i;

	i = 0;
    write(1, &"!!!!!!!!!!argument!!!!!!!!!!\n", 29);
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

void	init_index(t_all *a)
{
	a->p.i = 0;
	a->p.start = 0;
	a->p.count = 0;
}

int		main(void)
{
	t_all	*a;
	char	*line;

	a = malloc(sizeof(t_all) * 1);
    init(a);
	while (1)
	{
		init_index(a);
		get_next_line(0, &line);
		parsing(a, line);
		show_com(a);
		show_arg(a);
        ft_free_mat(a->arguments);
		if (a->arguments)
		{
			free(a->arguments);
			a->arguments = NULL;
		}
		if (a->command)
		{
			free(a->command);
			a->command = NULL;
		}
		parsing(a, line);
		show_com(a);
		show_arg(a);
        ft_free_mat(a->arguments);
		if (a->arguments)
		{
			free(a->arguments);
			a->arguments = NULL;
		}
		if (a->command)
		{
			free(a->command);
			a->command = NULL;
		}
		free(line);
		system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	}
}
