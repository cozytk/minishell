/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:25:55 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/04 20:58:19 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    init(t_all *a)
{
	a->redirect = 0;
	a->cmd = NULL;
	a->arg = NULL;
}

void	init_index(t_all *a)
{
	a->p.i = 0;
	a->p.start = 0;
	a->p.count = 0;
	a->p.pipe = 0;
}

void	free_com_arg(t_all *a)
{
	ft_free_mat(a->arg);
	if (a->arg)
	{
		free(a->arg);
		a->arg = NULL;
	}
	if (a->cmd)
	{
		free(a->cmd);
		a->cmd = NULL;
	}
}

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

	argsize = ft_matrow(a->arg);
	new_mat = malloc(sizeof(char *) * (argsize + 2));
	i = 0;
	if (a->arg)
	{
		while (a->arg[i])
		{
			new_mat[i] = ft_strdup(a->arg[i]);
			i++;
		}
		ft_free_mat(a->arg);
        free(a->arg);
        a->arg = NULL;
	}
	new_mat[i] = arg;
	new_mat[i + 1] = NULL;
	a->arg = new_mat;
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

	if (!a->cmd)
		a->cmd = new;
	else
		add_argument(a, new);
	a->p.i++;
}

int		is_pipe_or_scolon(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
}

void	add_parsed(t_all *a, char *line)
{
	char	*temp;

	temp = ft_substr(line, a->p.start, a->p.count);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
		return ;
	}
	if (!a->cmd)
		a->cmd = temp;
	else
		add_argument(a, temp);

}

int     parsing(t_all *a)
{
	while (is_space(a->line[a->p.i]))
		a->p.i++;
	a->p.pipe = 0;
	a->p.start = a->p.i;
	while (a->line[a->p.i])
	{
		if (a->line[a->p.i] == '\\' && a->line[a->p.i - 1] != '\\')
		{
			add_parsed(a, a->line);
			a->p.i++;
			a->p.count = 1;
			a->p.back_flag = 1;
			a->p.start = a->p.i;
			add_parsed(a, a->line);
			a->p.count = 0;
			a->p.i++;
			a->p.start = a->p.i;
			continue;
		}
		if (is_pipe_or_scolon(a->line[a->p.i]))
		{
			if (a->line[a->p.i - 1] != ' ' && a->p.i > 1)
				add_parsed(a, a->line);
			if (a->line[a->p.i] == '|')
				a->p.pipe = 1;
			a->p.i++;
			a->p.start = a->p.i;
			a->p.count = 0;
			return (0);
		}
        else if (is_sep_char(a->line[a->p.i]))
        {
			if (a->line[a->p.i - 1] != ' ' && a->p.i > 1)
				add_parsed(a, a->line);
			a->p.start = a->p.i;
            a->p.count = 1;
			if (a->line[a->p.i] == '>' && a->line[a->p.i + 1] == '>')
				a->p.count++;
			add_argument(a, ft_substr(a->line, a->p.start, a->p.count));
            a->p.i += a->p.count;
			a->p.start = a->p.i;
			a->p.count = 0;
			continue ;
        }
		else if (is_quote(a->line[a->p.i]))
		{
			if (a->line[a->p.i - 1] != ' ' && a->p.i > 1)
				add_parsed(a, a->line);
			if (a->line[a->p.i] == '\'')
				s_quote_process(a, a->line);
			else if (a->line[a->p.i] == '\"')
				d_quote_process(a, a->line);
			a->p.start = a->p.i;
			while (is_space(a->line[a->p.i]))
			{
				a->p.i++;
				a->p.start++;
			}
			a->p.count = 0;
			continue ;
		}
		else if (is_space(a->line[a->p.i]))
		{
			add_parsed(a, a->line);
			quote_join(a);
			while (is_space(a->line[a->p.i]))
				a->p.i++;
			a->p.start = a->p.i;
			a->p.count = 0;
			continue;
		}
		a->p.count++;
		a->p.i++;
	}
	if (a->line[a->p.i - 1] != ' ')
		add_parsed(a, a->line);
	show_com(a);
	show_arg(a);
	return (1);
}

void	show_com(t_all *a)
{
    write(1, &"==========command==========\n", 28);
	if (!a->cmd)
		return ;
	write(1, &"[", 1);
	write(1, a->cmd, ft_strlen(a->cmd));
	write(1, &"]", 1);
	write(1, &"\n", 1);
}

void	show_arg(t_all *a)
{
	int		i;

	i = 0;
	if (!a->arg)
		return ;
    write(1, &"!!!!!!!!!!argument!!!!!!!!!!\n", 29);
	while (a->arg[i])
	{
		write(1, &"[", 1);
		write(1, a->arg[i], ft_strlen(a->arg[i]));
		write(1, &"]", 1);
		write(1, &"\n", 1);
		i++;
	}
	printf("!!!!!!!!!!!argument end!!!!!!!!!!!!\n");
}
