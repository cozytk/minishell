#include "../inc/minishell.h"

void	equal_process2(t_all *a, char *env)
{
	int		i;

	i = 0;
	if ((i = find_row(a->sub_env, env)) != -1)
		a->sub_env = ft_delete_row(a->sub_env, i);
	a->sub_env = add_row(a->sub_env, a->p.candidate);
}

void	equal_process(t_all *a)
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
	while (a->p.candidate[i] != '=')
	{
		env = ft_strcjoin(env, a->p.candidate[i]);
		i++;
	}
	env = ft_strcjoin(env, a->p.candidate[i]);
	if ((i = find_row(a->env, env)) != -1)
	{
		a->cmd = ft_strdup("export");
		add_argument(a, a->p.candidate);
		export(a);
		free(a->cmd);
		a->cmd = NULL;
		ft_free_mat(a->arg);
		a->arg = NULL;
	}
	else
		equal_process2(a, env);
	if (env)
		free(env);
}
