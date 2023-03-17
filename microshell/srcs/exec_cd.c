/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:38:07 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:22:07 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_path_and_old(char *path, t_shell *shell)
{
	t_varble	*temp;
	t_varble	*new;

	new = shell->variable;
	temp = shell->variable;
	while (ft_strcmp(temp->var_name, "PWD") != 1 && temp)
		temp = temp->next;
	while (ft_strcmp(new->var_name, "OLDPWD") != 1 && new)
		new = new->next;
	new->var_data = ft_strdup(temp->var_data);
	new->entire_var = ft_strjoin(new->var_name, new->var_data);
	temp->var_data = ft_add_path(path, shell, temp->var_data);
	temp->entire_var = ft_strjoin(temp->var_name, temp->var_data);
}

char	*ft_add_path(char *path, t_shell *shell, char *old)
{
	char	*temp;
	int		i;
	int		j;

	(void)shell;
	j = 0;
	i = 0;
	temp = malloc(sizeof(char) * ((ft_strlen(path) + ft_strlen(old) + 2)));
	while (old[i] != '\0')
	{
		temp[i] = old[i];
		i++;
	}
	temp[i++] = '/';
	while (path[j])
	{
		temp[i] = path[j];
		j++;
		i++;
	}
	if (temp[i - 1] == '/')
		temp[i - 1] = '\0';
	temp[i] = '\0';
	return (temp);
}

void	change_back_cd(t_shell *shell)
{
	t_varble	*temp;
	t_varble	*new;

	temp = shell->variable;
	new = shell->variable;
	while (ft_strcmp(temp->var_name, "OLDPWD") != 1 && temp)
		temp = temp->next;
	temp->var_data = ft_strdup(get_pwd(shell));
	temp->entire_var = ft_strjoin(temp->var_name, get_pwd(shell));
	while (ft_strcmp(new->var_name, "PWD") != 1 && new)
		new = new->next;
	new->var_data = del_one_path(shell);
	new->entire_var = ft_strjoin(new->var_name, new->var_data);
}

void	cd_home_change(t_shell *shell)
{
	t_varble	*temp;
	t_varble	*new;

	temp = shell->variable;
	new = shell->variable;
	while (ft_strcmp(temp->var_name, "OLDPWD") != 1 && temp)
		temp = temp->next;
	temp->var_data = ft_strdup(get_pwd(shell));
	temp->entire_var = ft_strjoin(temp->var_name, get_pwd(shell));
	while (ft_strcmp(new->var_name, "PWD") != 1 && new)
		new = new->next;
	new->var_data = get_home(shell);
	new->entire_var = ft_strjoin(new->var_name, new->var_data);
}

char	*get_oldpwd(t_shell *shell)
{
	t_varble	*temp;

	temp = shell->variable;
	while (ft_strcmp(temp->var_name, "OLDPWD") != 1 && temp)
		temp = temp->next;
	return (temp->var_data);
}
