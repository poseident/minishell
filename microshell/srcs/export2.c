/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:57:04 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:18:48 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export_change_var_redir(t_shell *shell, char **source)
{
	t_varble	*tmp;
	int			i;
	char		*var;

	i = 0;
	while (source[++i])
	{
		tmp = shell->variable;
		var = ft_fill_variable_name(source[i]);
		while (tmp)
		{
			if (ft_strchr(tmp->var_name, var) == 1)
				ft_change_data(tmp, source[i]);
			tmp = tmp->next;
		}
	}
	return ;
}

void	ft_exec_export_redir(t_shell *shell, char **source)
{
	int			i;
	t_varble	*temp;
	char		*name;

	i = 0;
	while (source[++i])
	{
		temp = shell->variable;
		name = ft_fill_variable_name(source[i]);
		while (temp)
		{
			if (ft_strchr(name, temp->var_name) == 1)
				temp->in_env = 1;
			temp = temp->next;
		}
	}
	ft_export_change_var_redir(shell, source);
	ft_export_add3(shell, source);
}

void	ft_change_data(t_varble *tmp, char *var)
{
	tmp->var_data = ft_get_var_data(var);
	tmp->entire_var = ft_strdup(var);
	tmp->in_env = 1;
}

void	ft_export_change_var(t_shell *shell)
{
	t_varble	*tmp;
	int			i;
	char		*var;

	i = 0;
	while (shell->split_ipt[++i])
	{
		tmp = shell->variable;
		var = ft_var_name(shell->split_ipt[i]);
		while (tmp)
		{
			if (ft_strchr(tmp->var_name, var) == 1)
			{
				ft_change_data(tmp, shell->split_ipt[i]);
				shell->split_ipt = ft_change_split_input2(shell, i);
				i = 0;
				break ;
			}
			else
				tmp = tmp->next;
		}
	}
	return ;
}

char	**ft_change_split_input2(t_shell *shell, int i)
{
	char	**tmp;
	int		j;
	int		h;

	h = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * shell->split_input_size);
	while (shell->split_ipt[j])
	{
		if (i != j)
		{
			tmp[h] = ft_strdup(shell->split_ipt[j]);
			h++;
			j++;
		}
		else
			j++;
	}
	tmp[h] = 0;
	shell->split_input_size -= 1;
	return (tmp);
}
