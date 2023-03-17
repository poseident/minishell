/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:04:41 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:20:57 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	gestion_heredoc(char *arg_stop)
{
	int		fd;
	char	*str;

	fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		str = readline("\033[32mheredoc> \033[0m");
		if (ft_strcmp(str, arg_stop) == 1)
			break ;
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (fd);
}

int	exec_cmd(char **cmd, int fd_in, int fd_out, t_shell *shell)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (!pid)
		ft_child_fonc(cmd, fd_in, fd_out, shell);
	else
		waitpid(pid, &status, 0);
	return (1);
}

void	input_redirection(t_pipe *redir, t_shell *shell, t_exec *exec)
{
	(void)shell;
	exec->out_gestion = 1;
	if (ft_strcmp(redir->redir, "<") == 1)
	{
		exec->fd_entry = open(redir->redir_dest[0], O_RDWR);
	}
	if (ft_strcmp(redir->redir, "<<") == 1)
		ft_heredoc(redir, exec, shell);
	return ;
}

void	ft_putnbr_fd(int nb, int fd)
{
	long int	c;

	c = nb;
	if (c < 0)
	{
		ft_putchar_fd('-', fd);
		c = -c;
	}
	if (c > 9)
	{
		ft_putnbr_fd(c / 10, fd);
		ft_putnbr_fd(c % 10, fd);
	}
	else
		ft_putchar_fd(c + '0', fd);
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
