/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:25:55 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/04 22:06:45 by taehkim          ###   ########.fr       */
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

char	*get_env_by_arg(char *arg)
{
	int		i;
	int		start;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '{')
			{
				start = i + 2;
				while (arg[i] != '}' && arg[i])
					i++;
				if (!arg[i])
					return (NULL);
				return (ft_substr(arg, start, i - start));
			}
			else
			{
				start = i + 1;
				while (arg[i] && arg[i] != ' ')
					i++;
				return (ft_substr(arg, start, i - start));
			}
		}
		i++;
	}
	return (NULL);
}

char	*find_env_result(t_all *a, char *env)
{
	int		i;
	int		j;
	int		start;
	char	*temp;

	i = 0;
	while (a->env[i])
	{
		if (!ft_strncmp(a->env[i], env, ft_strlen(env)))
		{
			j = 0;
			while (a->env[i][j] != '=')
				j++;
			j++;
			start = j;
			while (a->env[i][j])
				j++;
			temp = ft_substr(a->env[i], start, j - start);
			free(env);
			return (temp);
		}
		i++;
	}
	free(env);
	return (NULL);
}
/*
char	*replace_env_result(t_all *a, char *arg, char *env)
{
	char	*temp;
	char	*replace;
	char	*temp2;
	int		i;
	int		start;

	i = 0;
	while (arg[i] && arg[i] != '$')
		i++;
	temp = ft_substr(arg, 0, i);
	if (!temp[0])
	{
		free(temp);
		temp = NULL;
	}
	if (arg[++i] == '{')
		while (arg[i] != '}')
			i++;
	start = i;
	while (arg[i])
		i++;
	temp2 = ft_substr(arg, start, i - start);
	if (!temp2[0])
	{
		free(temp2);
		temp2 = NULL;
	}
	if (temp && env)
	{
		replace = ft_strjoin(temp, env);
		free(temp);
	}
	if (temp2 && env)
	{

	}
}
*/

void	process_env(t_all *a, char *arg)
{
	char	*env;
	char	*result;

	//${USER}eee
	//"${USER}eee"
	//aaa$USERbbb
	//printf("cmd : %s\n", a->cmd);
	env = get_env_by_arg(arg);
	if (env)
		result = find_env_result(a, env);
	else
		return ;
	//env = replace_env_result(a, arg, env);
	int size = ft_matrow(a->arg) - 1;
	a->arg = ft_delete_row(a->arg, size);
	if (result)
		add_argument(a, result);
	//printf("%s\n", env);
	//return (arg);
	//return (env);
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

int		is_pipe_or_scolon(char c)
{
	if (c == '|' || c == ';')
		return (1);
	return (0);
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
			a->p.start += a->p.count;
			a->p.count = 2;
			add_parsed(a, a->line);
			a->p.count = 0;
			a->p.i += 2;
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
			//printf("%c\n", a->line[a->p.i]);
			a->p.count = 0;
			continue ;
		}
		else if (is_space(a->line[a->p.i]))
		{
			add_parsed(a, a->line);
			int size = ft_matrow(a->arg) - 1;
			if (size >= 0)
				process_env(a, a->arg[size]);
			while (is_space(a->line[a->p.i]))
				a->p.i++;
			a->p.start = a->p.i;
			a->p.count = 0;
			continue;
		}
		else if (a->line[a->p.i + 1] == '\0')
		{
			a->p.count++;
			add_parsed(a, a->line);
			int size = ft_matrow(a->arg) - 1;
			if (size >= 0)
				process_env(a, a->arg[size]);
			break;
		}
		a->p.count++;
		a->p.i++;
	}
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
