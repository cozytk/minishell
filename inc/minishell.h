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
	char **env;
}					t_all;

int			get_next_line(int fd, char **line);
char		*ft_strdup_til_enter(const char *s1);
void		after_enter(char **str, int spot);
char		*gnl_strjoin(char *s1, char *s2);
void		init_env(char **env, t_all *a);

#endif
