/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:08:26 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/11 21:12:53 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# define PROMPT_MSG " $"
# define WELCOME_MSG " welcome.\n"
# define PT_COLOR_LEFT "\e[42;1;37m"
# define PT_COLOR_RIGHT "\e[0m"

# define INIT "bash-3.2$ "

typedef struct	s_parse
{
	int		i;
	int		start;
	int		pipe;
	int		s_colon;
	int		parsing;
	int		end;
	char	*candidate;
	char	*tmp;
	char	*tmp2;
}				t_parse;

typedef struct	s_all
{
	char	**env;
	char	**ept;
	char	**arg;
	char	**sub_env;
	int		fd[2];
	char	*cmd;
	char	*line;
	char	init_home[1024];
	int		fileno;
	int		redirect;
	int		fd_tmp;
	int		cd;
	t_parse	p;
}				t_all;

int				g_end;

void			free_all(t_all *a);
char			**check_identifier(char **mat);
void			ft_erase(void);
int				cmd_itself(char *cmd, char *str);
void			init_struct(t_all *a);
int				has_identifier(char *str);
int				write_error(char *cmd, char *str, char *err, int exit);
void			init(t_all *a);
int				cmd_exec(t_all *a);
int				cmd_builtin(t_all *a);
void			bash_cmd_error(char *cmd, char *msg, int exit_code);
int				export(t_all *a);
int				cd(t_all *a);
int				echo(t_all *a);
int				cmd_itself(char *cmd, char *str);
int				pwd(t_all *a);
int				env(t_all *a);
int				unset(t_all *a);
char			**check_overlap(char **mat);
char			**ft_delete_row(char **mat, int del);
int				get_next_line(int fd, char **line);
char			*ft_strdup_til_enter(const char *s1);
void			after_enter(char **str, int spot);
char			*gnl_strjoin(char *s1, char *s2);
void			init_env(char **env, t_all *a);
void			init_export(t_all *all, char **env);
void			init_struct(t_all *a);
void			sort_mat(char **env);
int				ft_pipe(t_all *a);
int				redirect(t_all *a);
int				main_loop(t_all *a);
int				ft_exit(t_all *a);
int				find_row(char **mat, char *s);
int				find_exact_row(char **mat, char *s);
char			**ft_matadd_front(t_all *a);

/*
**	parse functions (taehkim)
*/

void			add_argument(t_all *a, char *arg);
void			show_arg(t_all *a);
void			show_com(t_all *a);
void			free_com_arg(t_all *a);
int				parsing(t_all *a);
int				is_sep_char(char c);
int				chk_only_space(char *arg);
int				is_space(char c);
int				is_quote(char c);
int				is_pipe_or_scolon(char c);
char			*get_env_by_arg(t_all *a, char *arg, int *count);
char			*get_env_by_arg2(t_all *a, char *arg, int *count, int i);
char			*get_env_by_arg3(t_all *a, char *arg, int *count, int i);
char			*find_env_result(t_all *a, char *env, int i, int j);
char			*process_env(t_all *a, char *arg);
void			s_quote_process(t_all *a);
void			d_quote_process(t_all *a);
void			quote_join(t_all *a);
void			parse_init(t_all *a);
int				parse_pipe_scolon(t_all *a);
void			parse_redirect(t_all *a);
void			parse_quote(t_all *a);
void			parse_one(t_all *a);
int				parse_last(t_all *a);
void			add_candidate(t_all *a);
int				validate(t_all *a);
int				show_prompt(void);
void			equal_process(t_all *a);
char			**add_row(char **mat, char *arg);
int				same_key(char *s1, char *s2);
void			write_quote(char *str);

#endif
