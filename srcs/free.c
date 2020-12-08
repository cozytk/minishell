#include "../inc/minishell.h"

void	free_com_arg(t_all *a)
{
	ft_free_mat(a->arg);
	ft_free_mat(a->ept);
	if (a->arg)
		a->arg = NULL;
	if (a->cmd)
	{
		free(a->cmd);
		a->cmd = NULL;
	}
	if (a->ept)
		a->ept = NULL;
}
