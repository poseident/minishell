/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:53:08 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 00:32:04 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup_modified(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	ft_export_add2(t_varble *tmp, char *var)
{
	t_varble	*newnode;

	newnode = (struct s_varble *)malloc(sizeof(struct s_varble));
	newnode->var_data = ft_fill_variable_data(var);
	newnode->var_name = ft_fill_variable_name(var);
	newnode->entire_var = ft_strdup(var);
	newnode->deleted = 0;
	newnode->in_env = 1;
	newnode->next = NULL;
	tmp->next = newnode;
	tmp = tmp->next;
	return ;
}

void	ft_export_add(t_shell *shell)
{
	t_varble	*tmp;
	int			i;

	i = 0;
	tmp = shell->variable;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (shell->split_ipt[++i])
	{
		if (ft_variable_check_2(shell->split_ipt[i], -1) == 1)
		{
			ft_export_add2(tmp, shell->split_ipt[i]);
			tmp = tmp->next;
		}
	}
	return ;
}

void	ft_exec_export(t_shell *shell)
{
	int			i;
	t_varble	*temp;

	i = 0;
	while (shell->split_ipt[++i])
	{
		temp = shell->variable;
		while (temp)
		{
			if (ft_strchr(shell->split_ipt[i], temp->var_name) == 1)
			{
				shell->split_ipt = ft_change_split_input2(shell, i);
				temp->in_env = 1;
				i = 0;
				break ;
			}
			else
				temp = temp->next;
		}
	}
	ft_export_change_var(shell);
	ft_export_add(shell);
}

char	*ft_var_name(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '=')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
