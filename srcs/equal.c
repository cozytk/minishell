#include "../inc/minishell.h"

void	equal_process(t_all *a)
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
	//a->p.tmp = NULL;
	while (a->p.candidate[i] != '=')
	{
		env = ft_strcjoin(env, a->p.candidate[i]);
		i++;
	}
	if ((i = find_row(a->env, env)) != -1)
	{
		a->cmd = ft_strdup("export");
		add_argument(a, a->p.candidate);
		export(a);
	}
	/*
	else
		a->sub_env = add_row(a->sub_env, a->p.candidate);
		*/
	if (env)
		free(env);
}
