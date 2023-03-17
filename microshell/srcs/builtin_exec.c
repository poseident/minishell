/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:34:20 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:19:41 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_pwd(t_shell *shell)
{
	t_varble	*temp;

	temp = shell->variable;
	while (ft_strcmp(temp->var_name, "PWD") != 1 && temp)
		temp = temp->next;
	return (temp->var_data);
}

char	*get_home(t_shell *shell)
{
	t_varble	*temp;

	temp = shell->variable;
	while (ft_strcmp(temp->var_name, "HOME") != 1 && temp)
		temp = temp->next;
	return (temp->var_data);
}

void	ft_exec_bin(t_shell *shell)
{
	pid_t	pid;
	char	*str;

	pid = fork();
	if (pid == 0)
	{
		ft_get_path(shell);
		str = ft_strjoin("/bin/", shell->split_ipt[0]);
		if (execve(str, shell->input_ls, NULL) == -1)
			exit(0);
	}
	wait(&pid);
}

void	ft_exec_exit(t_shell *shell)
{
	t_varble	*tmp;
	int			i;

	i = 0;
	while (shell->split_ipt[i])
	{
		free(shell->split_ipt[i]);
		i++;
	}
	free(shell->split_ipt[i]);
	free(shell->split_ipt);
	tmp = shell->variable;
	while (shell->variable->next)
	{
		shell->variable = shell->variable->next;
		free(tmp);
		tmp = shell->variable;
	}
	exit(0);
	return ;
}

void	ft_exec_cd(t_shell *shell, char *path)
{
	if (!path)
	{
		path = get_home(shell);
		cd_home_change(shell);
		if (chdir(path) != -1)
			shell->sucess_cmd = 0;
		else
		{
			printf("No such file or directory\n");
			shell->sucess_cmd = 1;
		}
		return ;
	}
	else
		ft_exec_cd2(shell, path);
}
