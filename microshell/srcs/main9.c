/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:10:43 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:21:11 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_lexer_simplify_count(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			str[i++] = '\\';
			while (str[i] != '"' && str[i] != '\0')
				str[i++] = 'x';
			if (str[i] == '\0')
				return (0);
			str[i] = '\\';
		}
		else if (str[i] == 39)
		{
			str[i++] = '\\';
			while (str[i] != 39 && str[i] != '\0')
				str[i++] = 'x';
			if (str[i] == '\0')
				return (0);
			str[i] = '\\';
		}
	}
	return (&str[0]);
}

void	ft_export_add3(t_shell *shell, char **source)
{
	t_varble	*tmp;
	int			i;

	i = 0;
	tmp = shell->variable;
	while (tmp->next != NULL)
		tmp = tmp->next;
	export_add4(tmp, source, shell, 0);
	return ;
}

void	ft_exec_bin2(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		{
			ft_get_path(shell);
			if (execve(shell->split_ipt[0], shell->input_ls, NULL) == -1)
				exit(0);
		}
	}
	wait(&pid);
}

int	redir_error(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (ft_strcmp(input[i - 1], ">") == 1)
		return (-1);
	if (ft_strcmp(input[i - 1], ">>") == 1)
		return (-1);
	if (ft_strcmp(input[i - 1], "<") == 1)
		return (-1);
	if (ft_strcmp(input[i - 1], "<<") == 1)
		return (-1);
	if (ft_redir_check2(input) == -1)
		return (-1);
	return (0);
}

void	exec_other(t_shell *shell)
{
	if (sep_error(shell->split_ipt) != -1
		&& (redir_error(shell->split_ipt) != -1))
	{
		if (cmd_after_pipe_error(shell->split_ipt) != -1)
			ft_init_struct(shell);
		else
		{
			printf("expect command after pipe\n");
			return ;
		}
	}
	else
	{
		printf("syntax error\n");
		return ;
	}
}
