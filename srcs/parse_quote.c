#include "../inc/minishell.h"

void	s_quote_process(t_all *a, char *line)
{
	int		start;
	char	*temp;
	char	*temp2;
	char	*new;
	int		end_flag;

	a->p.count = 0;
	a->p.i++;
	if (line[a->p.i] == '\'')
	{
		a->p.i++;
		a->p.start = a->p.i;
		return ;
	}
	start = a->p.i;
	new = ft_strdup("");
	end_flag = 0;
	while (line[a->p.i] != '\'' || end_flag == 1)
	{
		if (line[a->p.i] == '\\')
		{
			temp = ft_strdup(new);
			temp2 = ft_substr(line, start, a->p.count);
			free(new);
			new = NULL;
			new = ft_strjoin(temp, temp2);
			free(temp);
			temp = NULL;
			free(temp2);
			temp2 = NULL;
			a->p.count = 0;
			a->p.i++;
			start = a->p.i;
			end_flag = 1;
			continue;
		}
		if (line[a->p.i] == '\0')
		{
			write(1, "> ", 2);
			while (1);
		}
		end_flag = 0;
		a->p.count++;
		a->p.i++;
	}
	temp = ft_strdup(new);
	temp2 = ft_substr(line, start, a->p.count);
	free(new);
	new = NULL;
	new = ft_strjoin(temp, temp2);
	free(temp);
	temp = NULL;
	free(temp2);
	temp2 = NULL;
	if (new[0] == '\0')
	{
		free(new);
		new = NULL;
		return ;
	}
	if (!a->cmd)
		a->cmd = new;
		//a->cmd = ft_substr(line, start, a->p.count);
	else
		//add_argument(a, ft_substr(line, start, a->p.count));
		add_argument(a, new);
	a->p.i++;
}


void	d_quote_process(t_all *a, char *line)
{
	int		start;
	char	*temp;
	char	*temp2;
	char	*new;
	int		end_flag;

	a->p.count = 0;
	a->p.i++;
	if (line[a->p.i] == '\"')
	{
		a->p.i++;
		a->p.start = a->p.i;
		return ;
	}
	start = a->p.i;
	new = ft_strdup("");
	end_flag = 0;
	while (line[a->p.i] != '\"' || end_flag == 1)
	{
		if (line[a->p.i] == '\\')
		{
			temp = ft_strdup(new);
			temp2 = ft_substr(line, start, a->p.count);
			free(new);
			new = NULL;
			new = ft_strjoin(temp, temp2);
			free(temp);
			temp = NULL;
			free(temp2);
			temp2 = NULL;
			a->p.count = 0;
			a->p.i++;
			start = a->p.i;
			end_flag = 1;
			continue;
		}
		if (line[a->p.i] == '\0')
		{
			write(1, "> ", 2);
			while (1);
		}
		end_flag = 0;
		a->p.count++;
		a->p.i++;
	}
	temp = ft_strdup(new);
	temp2 = ft_substr(line, start, a->p.count);
	free(new);
	new = NULL;
	new = ft_strjoin(temp, temp2);
	free(temp);
	temp = NULL;
	free(temp2);
	temp2 = NULL;
	if (new[0] == '\0')
	{
		free(new);
		new = NULL;
		return ;
	}
	//new = process_env(a, new);
	if (!a->cmd)
		a->cmd = new;
	else
		add_argument(a, new);
	process_env(a, new);
	a->p.i++;
}

void	quote_join(t_all *a)
{
	int		size;
	//char	*str = "\"";

	size = ft_matrow(a->arg);
	//printf("%s\n", str);
	//printf("%d\n", ft_strncmp(str, "\"\0", 2));
	if (size >= 2)
	{
		if (a->arg[size - 2][0] == '\\' &&
				a->arg[size - 1][0] == '\\')
		{
			add_argument(a, ft_strjoin(&a->arg[size - 2][1], &a->arg[size - 1][1]));
			a->arg = ft_delete_row(a->arg, size - 1);
			a->arg = ft_delete_row(a->arg, size - 2);
		}
		else if (a->arg[size - 2][0] == '\\')
		{
			add_argument(a, ft_strjoin(&a->arg[size - 2][1], a->arg[size - 1]));
			a->arg = ft_delete_row(a->arg, size - 1);
			a->arg = ft_delete_row(a->arg, size - 2);
		}
		else if (a->arg[size - 1][0] == '\\')
		{
			add_argument(a, ft_strjoin(a->arg[size - 2], &a->arg[size - 1][1]));
			a->arg = ft_delete_row(a->arg, size - 1);
			a->arg = ft_delete_row(a->arg, size - 2);
		}
	}
}

