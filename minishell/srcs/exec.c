/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:57:26 by cdescour          #+#    #+#             */
/*   Updated: 2022/12/02 16:55:31 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int builtin_exec(t_shell *shell)
{
    if (ft_builtin_check(shell->split_input[0], "env") == 1)
    {
        if (!shell->split_input[1])
            ft_print_env(shell);
        else
            printf("too much argument for env\n");
    }
    if (ft_builtin_check(shell->split_input[0], "pwd") == 1)
    {
        if (!shell->split_input[1])
            printf ("%s\n", ft_print_pwd(shell->arg));
        else
            printf("too much argument for pwd\n");
    }
	if (ft_builtin_check(shell->split_input[shell->index], "echo") == 1)
        ft_echo(shell->split_input, shell);
    if (ft_builtin_check(shell->split_input[shell->index], "export") == 1)
        ft_exec_export(shell);
    if (ft_builtin_check(shell->split_input[shell->index], "unset") == 1)
        ft_exec_unset(shell);
    return (1);
}

void ft_exec_command(t_shell *shell)
{
    if (builtin_exec(shell) == 1)
        return ;
    return ;
}
