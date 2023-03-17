/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:40:00 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:23:57 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_input_size(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->split_ipt[i])
		i++;
	return (i);
}

void	ft_init_chain(t_shell *shell, char **env)
{
	shell->variable = malloc(sizeof(t_varble));
	shell->variable->var_data = ft_fill_variable_data(env[0]);
	shell->variable->var_name = ft_fill_variable_name(env[0]);
	shell->variable->entire_var = NULL;
	shell->variable->deleted = 0;
	shell->variable->in_env = 0;
	shell->variable->next = NULL;
	ft_init_env2(shell, env);
	ft_init_simple_argv(shell);
}

void	ft_init_simple_argv(t_shell *shell)
{
	shell->simple_av = malloc(sizeof(char *) * 2);
	shell->simple_av[0] = malloc(sizeof(char) * 12);
	shell->simple_av[0] = "./minishell";
	shell->simple_av[1] = 0;
	return ;
}

void	ft_init_env2(t_shell *shell, char **env)
{
	int			i;
	t_varble	*temp;
	t_varble	*newnode;

	temp = shell->variable;
	i = 1;
	while (env[i])
	{
		newnode = (t_varble *)malloc(sizeof(t_varble));
		newnode->var_data = ft_fill_variable_data(env[i]);
		newnode->var_name = ft_fill_variable_name(env[i]);
		newnode->entire_var = ft_strdup(env[i]);
		newnode->deleted = 0;
		newnode->in_env = 1;
		newnode->next = NULL;
		temp->next = newnode;
		temp = temp->next;
		i++;
	}
	return ;
}
