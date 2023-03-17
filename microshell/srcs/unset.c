/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:19:14 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:21:51 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_unset(t_shell *shell)
{
	int			i;
	t_varble	*tmp;

	i = 0;
	while (shell->split_ipt[++i])
	{
		tmp = shell->variable;
		while (tmp)
		{
			if (ft_strchr(shell->split_ipt[i], tmp->var_name) == 1)
			{
				tmp->deleted = 1;
				tmp->in_env = 0;
				break ;
			}
			else
				tmp = tmp->next;
		}
	}
	return ;
}
