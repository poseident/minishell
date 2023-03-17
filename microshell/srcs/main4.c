/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:06:07 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:20:07 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	built_in_pwd(int fd)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd()");
	else
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	built_in_echo(char **message, int fd)
{
	int	i;

	i = 1;
	if (message[1])
		if (ft_strcmp(message[1], "-n") == 0)
			i++;
	while (message[i])
	{
		ft_putstr_fd(message[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	if (message[1])
	{
		if (ft_strcmp(message[1], "-n") != 0)
			ft_putchar_fd('\n', fd);
	}
	else
		ft_putchar_fd('\n', fd);
}

void	built_in_env(t_shell *shell, int fd)
{
	while (shell->variable)
	{
		if (shell->variable->in_env == 1)
		{
			ft_putstr_fd(shell->variable->entire_var, fd);
			ft_putchar_fd('\n', fd);
		}
		shell->variable = shell->variable->next;
	}
}

void	ft_exec_built_in(t_pipe *redir, t_exec *exec, t_shell *shell)
{
	if (exec->fd_entry != 0)
	{
		dup2(exec->fd_entry, STDIN_FILENO);
		close(exec->fd_entry);
	}
	if (ft_strcmp(redir->redir_source[0], "pwd") == 1)
		built_in_pwd(exec->fd[1]);
	if (ft_strcmp(shell->first_cmd[0], "echo") == 1)
		ft_echo_fd(shell->first_cmd, shell, exec->fd[1]);
	else if (ft_strcmp(redir->redir_source[0], "env") == 1)
		built_in_env(shell, exec->fd[1]);
	if (ft_strcmp(redir->redir_source[0], "cd") == 1)
		ft_exec_cd(shell, redir->redir_source[1]);
	else if (ft_strcmp(redir->redir_source[0], "export") == 1)
		ft_exec_export_redir(shell, redir->redir_source);
	else if (ft_strcmp(redir->redir_source[0], "unset") == 1)
		ft_exec_unset(shell);
	else if (ft_strcmp(redir->redir_source[0], "exit") == 1)
		exit(0);
	else
		return ;
}
