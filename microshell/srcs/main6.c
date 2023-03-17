/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:08:15 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:23:30 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redirection(t_shell *shell)
{
	t_exec	exec;

	exec.fd[1] = 1;
	exec.fd[0] = 0;
	exec.out_gestion = 0;
	exec.fd_entry = STDIN_FILENO;
	while (shell->str_pipe)
	{
		if ((ft_strcmp(shell->str_pipe->redir, ">") == 1)
			|| (ft_strcmp(shell->str_pipe->redir, ">>") == 1))
			output_redirection(&exec.out_gestion, shell->str_pipe, &exec.fd[1]);
		else if ((ft_strcmp(shell->str_pipe->redir, "<") == 1)
			|| (ft_strcmp(shell->str_pipe->redir, "<<") == 1))
			input_redirection(shell->str_pipe, shell, &exec);
		else
			return ;
		if (exec.out_gestion != 1 && exec.out_gestion != 2)
		{
			exec.fd[1] = STDOUT_FILENO;
		}
		ft_interation_gestion(shell->str_pipe, shell, &exec);
		shell->env = new_env(shell);
		shell->str_pipe = shell->str_pipe->next;
	}
}

int	ft_builtin_checker2(char *str)
{
	if (ft_builtin_check(str, "pwd") == 1)
		return (1);
	if (ft_builtin_check(str, "echo") == 1)
		return (1);
	if (ft_builtin_check(str, "exit") == 1)
		return (1);
	if (ft_builtin_check(str, "env") == 1)
		return (1);
	if (ft_builtin_check(str, "unset") == 1)
		return (1);
	if (ft_builtin_check(str, "export") == 1)
		return (1);
	if (ft_builtin_check(str, "cd") == 1)
		return (1);
	else
		return (-1);
}

int	get_source_len(char **input, int redir)
{
	int	count;
	int	i;

	if (redir == 0)
		return (0);
	i = redir - 1;
	count = 0;
	while (redir_array_or_not(input[i]) != 1 && i > 0)
	{
		count++;
		i--;
	}
	return (count);
}

char	**source_redir(char **input, int redir)
{
	int		i;
	char	**source;

	source = malloc(sizeof(char *) * (get_source_len(input, redir) + 2));
	i = 0;
	while (i < redir)
	{
		source[i] = ft_strdup(input[i]);
		i++;
	}
	source[i] = NULL;
	return (source);
}

int	get_dest_len(char **input, int redir)
{
	int	count;
	int	i;

	count = 0;
	i = redir + 1;
	while (input[i] && (redir_array_or_not(input[i]) != 1))
	{
		count++;
		i++;
	}
	return (count);
}
