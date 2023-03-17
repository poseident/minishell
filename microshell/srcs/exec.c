/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:57:26 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/20 01:24:37 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_path(t_shell *shell)
{
	t_varble	*tmp;

	tmp = shell->variable;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "PATH") == 1)
		{
			if (tmp->in_env == 0)
				return (-1);
			else
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_builtin_exec2(t_shell *shell)
{
	if (ft_builtin_check(shell->split_ipt[0], "env") == 1)
	{
		if (shell->split_ipt[1] != NULL)
			shell->sucess_cmd = 1;
		if (!shell->split_ipt[1])
			ft_print_env(shell);
		return ;
	}
	else if (ft_builtin_check(shell->split_ipt[0], "pwd") == 1)
	{
		printf("%s\n", ft_print_pwd(shell));
		shell->sucess_cmd = 0;
		return ;
	}
	else if (bin_check(shell) == 1)
		ft_builtincheck3(shell);
	else
	{
		shell->sucess_cmd = 1;
		printf("bash: %s : command not found\n", shell->split_ipt[0]);
	}
	return ;
}

int	builtin_exec(t_shell *shell)
{
	if (ft_builtin_check(shell->split_ipt[0], "echo") == 1)
	{
		ft_echo(shell->split_ipt, shell);
		shell->sucess_cmd = 0;
		return (0);
	}
	else if (ft_builtin_check(shell->split_ipt[0], "export") == 1)
	{
		if (!shell->split_ipt[1])
			ft_print_env(shell);
		else
			ft_exec_export(shell);
		shell->sucess_cmd = 0;
		return (0);
	}
	builtin_exec5(shell);
	return (0);
}

void	ft_exec_command(t_shell *shell)
{
	if (no_pipe(shell->split_ipt) == 0 && no_redir(shell->split_ipt) == 0)
		builtin_exec(shell);
	else
	{
		if (no_pipe(shell->split_ipt) == 0)
			exec_other(shell);
		else
			printf("not handled\n");
	}
	return ;
}
