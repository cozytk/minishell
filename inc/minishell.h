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

typedef struct		s_all
{
	char	**env;
	char	**ept;
}					t_all;

int			cmd_itself(char *cmd, char *str);
int 		pwd(char *str);
int		 	env(char *str, t_all *a);
int			keycmp(char *src, char *key);
int			unset(char *str, t_all *a);
void		check_overlap(char **mat);
char		**ft_delete_row(char **mat, int del);
int			get_next_line(int fd, char **line);
char		*ft_strdup_til_enter(const char *s1);
void		after_enter(char **str, int spot);
char		*gnl_strjoin(char *s1, char *s2);
void		init_env(char **env, t_all *a);
void		init_export(t_all *all, char **env);
void		sort_mat(char **env);

#endif
