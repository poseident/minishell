/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:49:56 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/20 00:28:52 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_change_split_input(t_shell *shell, int index)
{
	int		i;
	char	**tmp;
	int		j;

	j = 0;
	i = 0;
	tmp = malloc(sizeof(char *) * shell->split_input_size);
	while (shell->cleaned_variable[i])
	{
		if (i != index)
		{
			tmp[j] = ft_strdup(shell->cleaned_variable[i]);
			j++;
			i++;
		}
		else
			i++;
	}
	tmp[j] = 0;
	shell->input_size -= 1;
	return (tmp);
}

int	ft_variable_check_2(char *s, int i)
{
	int	double_quote;
	int	simple_quote;

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
	while (s[i++])
	{
		if (s[i - 1] == '"' && simple_quote == 1)
			double_quote = -double_quote;
		if (s[i - 1] == '\'' && double_quote == 1)
			simple_quote = -simple_quote;
		if ((s[i - 1] == '>' || s[i] == '<')
			&& double_quote == 1 && simple_quote == 1)
			return (-1);
	}
	return (1);
}

int	ft_variable_checker(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->split_ipt[i])
	{
		if (ft_variable_check_2(shell->split_ipt[i], -1) == -1)
		{
			return (-1);
		}
		i++;
	}
	shell->cleaned_variable = ft_clean_variable(shell);
	replace_simple_variable(shell);
	ft_fill_variable(shell);
	return (1);
}

int	ft_builtin_checker(t_shell *shell)
{
	if (ft_strncmp(shell->split_ipt[0], "/bin/", 4) == 0)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "ls") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "pwd") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "echo") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "exit") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "env") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "unset") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "export") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "cd") == 1)
		return (1);
	if (ft_builtin_check(shell->split_ipt[0], "cat") == 1)
		return (1);
	if (ft_variable_checker(shell) == 1)
		return (1);
	else
		return (-1);
}

int	ft_builtin_check(char *input, char *s)
{
	int	i;
	int	j;

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
