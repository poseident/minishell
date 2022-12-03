/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:49:56 by cdescour          #+#    #+#             */
/*   Updated: 2022/12/03 14:26:57 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_variable_check_2(char *s)
{
	int i;
	int double_quote;
	int simple_quote;

	i = -1;
    if (!s)
        return (-1);
	while (s[++i] != '=')
	{
		if ((s[i] == '\0') || (s[i] >= ':' && s[i] <= '@'))
			return (-1);
		if ((s[i] < '0' || s[i] > 'z') || (s[i] >= '[' && s[i] <= '`'))
			return (-1);
	}
	double_quote = 1;
	simple_quote = 1;
	while(s[i])
	{
		if (s[i] == '"' && simple_quote == 1)
			double_quote = -double_quote;
		if (s[i] == '\'' && double_quote == 1)
			simple_quote = -simple_quote;
		if ((s[i] == '>' || s[i] == '<') && double_quote == 1 && simple_quote == 1)
			return (-1);
		i++;
	}
	return (1);
}

int ft_variable_checker(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->split_input[i])
    {
        if (ft_variable_check_2(shell->split_input[i]) == -1)
		{
			return (-1);
		}
        i++;
    }
    ft_clean_variable(shell);
    ft_fill_variable(shell);
    return (1);
}

int ft_builtin_checker(t_shell *shell)
{
    if (ft_builtin_check(shell->split_input[shell->index], "ls") == 1)
         return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "pwd") == 1)
        return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "echo") == 1)
        return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "exit") == 1)
        return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "env") == 1)
        return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "unset") == 1)
        return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "export") == 1)
        return (1);
    if (ft_builtin_check(shell->split_input[shell->index], "cd") == 1)
        return (1);
    if (ft_variable_checker(shell) == 1)
        return (1);
    else
        return (-1);
}

int ft_builtin_check(char *input, char *s)
{
    int i;
    int j;

    j = 0;
    i = -1;
    while (input[++i])
    {
        if (i != 0)
		{
			if (input[i] == 34 && input[i + 1] == 39 && input[i - 1] == 39)
				return (-1);
			if (input[i] == 39 && input[i + 1] == 34 && input[i - 1] == 34)
				return (-1);
		}
		if (input[i] != s[j] && !(input[i] == 34 || input[i] == 39))
            return (-1);
		else if (input[i] == s[j])
        {
            if (s[j])
                j++;
        }
    }
    if (s[j] != '\0')
        return (-1);
    return (1);
}
