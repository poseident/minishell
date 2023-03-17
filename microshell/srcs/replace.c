/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:21:09 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:20:41 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_replace_simple_sub(t_varble *temp, t_shell *shell, int i)
{
	temp->var_data = ft_get_var_data(shell->cleaned_variable[i]);
	temp->entire_var = ft_strdup(shell->cleaned_variable[i]);
	temp->deleted = 0;
	shell->split_ipt = ft_change_split_input(shell, i);
	shell->cleaned_variable = ft_clean_variable(shell);
}

int	replace_simple_variable(t_shell *shell)
{
	char		*var;
	int			i;
	t_varble	*temp;

	i = -1;
	while (shell->cleaned_variable[++i] != NULL)
	{
		var = ft_var_name(shell->cleaned_variable[i]);
		temp = shell->variable;
		while (temp)
		{
			if (ft_strchr(var, temp->var_name) == 1)
			{
				ft_replace_simple_sub(temp, shell, i);
				i = -1;
				break ;
			}
			else
				temp = temp->next;
		}
	}
	return (1);
}
