/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:07:02 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:26:35 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_child_fonc(char **cmd, int fd_in, int fd_out, t_shell *shell)
{
	char	*path;

	(void)shell;
	path = cmd[0];
	path = ft_strjoin("/bin/", cmd[0]);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	execve(path, cmd, NULL);
	exit(0);
	close(fd_in);
	close(fd_out);
	free (path);
	return ;
}

int	exec_cmd2(char **cmd, int fd_in, int fd_out, t_shell *shell)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
		ft_child_fonc(cmd, fd_in, fd_out, shell);
	else
		waitpid(pid, &status, 0);
	if (access(cmd[1], F_OK) == -1)
		shell->sucess_cmd = 1;
	else
		shell->sucess_cmd = 0;
	return (1);
}

int	ft_builtin_checker4(char *str)
{
	if (ft_strncmp(str, "/bin/", 4) == 0)
		return (1);
	if (ft_builtin_check(str, "ls") == 1)
		return (1);
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
	if (ft_builtin_check(str, "cat") == 1)
		return (1);
	else
		return (-1);
}

int	ft_interation_gestion(t_pipe *redir, t_shell *shell, t_exec *exec)
{
	if (redir->redir_source[0]
		&& (ft_builtin_checker2(shell->split_ipt[0]) == 1))
		ft_exec_built_in(redir, exec, shell);
	else if ((exec->out_gestion != 2 && exec->out_gestion != 3))
		exec_cmd2(redir->redir_source, exec->fd_entry, exec->fd[1], shell);
	if (exec->out_gestion == 2)
		exec->fd[0] = exec->fd_entry;
	return (1);
}

void	output_redirection(int *out_gestion, t_pipe *redir, int *fd_out)
{
	if (ft_strcmp(redir->redir, ">") == 1)
		fd_out[0] = open(redir->redir_dest[0],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (ft_strcmp(redir->redir, ">>") == 1)
		fd_out[0] = open(redir->redir_dest[0],
				O_CREAT | O_APPEND | O_RDWR, 0777);
	out_gestion[0] = 1;
	return ;
}
