/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim <taehkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:45:30 by taehkim           #+#    #+#             */
/*   Updated: 2020/12/08 23:45:31 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_all *a)
{
	ft_free_mat(a->arg);
	ft_free_mat(a->ept);
	ft_free_mat(a->env);
	if (a->line)
		free(a->line);
	if (a->cmd)
		free(a->cmd);
}

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
