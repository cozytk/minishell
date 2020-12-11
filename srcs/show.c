#include "../inc/minishell.h"

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

int		show_prompt(void)
{
	char    *prompt;
	char    *temp;
	char	pwd[1024];

	getcwd(pwd, 1024);
	temp = ft_strjoin(PT_COLOR_LEFT, pwd);
	prompt = ft_strjoin(temp, PT_COLOR_RIGHT);
	free(temp);
	temp = NULL;
	write(1, prompt, ft_strlen(prompt));
	write(1, PROMPT_MSG, ft_strlen(PROMPT_MSG));
	free(prompt);
	prompt = NULL;
	return (1);
}
