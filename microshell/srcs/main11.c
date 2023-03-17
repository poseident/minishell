/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:18:52 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:25:24 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_cd2(t_shell *shell, char *path)
{
	if (chdir(path) != -1)
	{
		shell->sucess_cmd = 0;
		if (ft_strcmp(path, "..") != 1 && (ft_strcmp(path, ".") != 1))
			change_path_and_old(path, shell);
	}
	else
	{
		printf("No such file or directory\n");
		shell->sucess_cmd = 1;
	}
	if (ft_strcmp(path, "..") == 1)
		change_back_cd(shell);
	return ;
}

void	builtin_exec5(t_shell *shell)
{
	if (ft_builtin_check(shell->split_ipt[0], "unset") == 1)
	{
		ft_exec_unset(shell);
		shell->env = new_env(shell);
		shell->sucess_cmd = 0;
		return ;
	}
	else if (ft_builtin_check(shell->split_ipt[0], "exit") == 1)
	{
		ft_exec_exit(shell);
		return ;
	}
	else if (ft_builtin_check(shell->split_ipt[0], "cd") == 1)
	{
		ft_exec_cd(shell, shell->split_ipt[1]);
		return ;
	}
	ft_builtin_exec2(shell);
	return ;
}

void	ft_builtincheck3(t_shell *shell)
{
	char	*str;

	if (check_path(shell) == 1)
	{
		if (strncmp(shell->split_ipt[0], "/bin/", 5) == 0)
			ft_exec_bin2(shell);
		else
			ft_exec_bin(shell);
		if (shell->split_ipt[1])
		{
			str = ft_strdup(shell->split_ipt[ft_input_size(shell) - 1]);
			if (access(str, F_OK) == -1)
				shell->sucess_cmd = 1;
			else
				shell->sucess_cmd = 0;
			return ;
		}
	}
	return ;
}

void	export_add4(t_varble *tmp, char **source, t_shell *shell, int i)
{
	t_varble	*check;
	char		*name;

	while (source[++i])
	{
		name = ft_fill_variable_name(source[i]);
		check = shell->variable;
		while (check)
		{
			if (ft_strchr(check->var_name, name) == 1)
				break ;
			check = check->next;
		}
		if (!check)
		{
			if (ft_variable_check_2(source[i], -1) == 1)
			{
				ft_export_add2(tmp, source[i]);
				tmp = tmp->next;
			}
		}
	}
	return ;
}

int	bin_check(t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	while (shell->bin[i])
	{
		if (ft_strcmp(shell->bin[i], shell->split_ipt[0]) == 1)
			return (1);
		str = ft_strdup("/bin/");
		str = ft_strjoin(str, shell->bin[i]);
		if (ft_strcmp(str, shell->split_ipt[0]) == 1)
		{
			free(str);
			return (1);
		}
		free (str);
		i++;
	}
	return (-1);
}
