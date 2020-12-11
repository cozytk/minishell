
#include "libft.h"

char 	**ft_matadd_front(t_all *a)
{
	char	**dst;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup(a->cmd);
	tmp[1] = (void *)0;
	dst = ft_matjoin(tmp, a->arg);
	ft_free_mat(tmp);
	return (dst);
}
