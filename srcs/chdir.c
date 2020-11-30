/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:19:26 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/30 16:19:28 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 	parse_cd(char *str, t_all *a)
{
	char *tmp;

	tmp = get_arg(str);
	while (*str && *str )
}

int 	chdir(char *str, t_all *a)
{
	if (cmd_itself("cd", str))
		cd_home(a);
	else if (!ft_strncmp(str, "cd ", 3))
		parse_cd(str + 3, a);
}
