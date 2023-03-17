/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:03:06 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:22:39 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_error_red2(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		if (tab[i][0] == '\'' || tab[i][0] == '"')
			continue ;
		while (tab[i][++j])
		{
			if (tab[i][j] == '<' || tab[i][j] == '>')
			{
				if (j == 0)
					return (0);
				else
					return (1);
			}
		}
	}
	return (0);
}

int	ft_error_red(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		if (tab[i][0] == '\'' || tab[i][0] == '"')
			continue ;
		while (tab[i][++j])
		{
			if (tab[i][j] == '<' || tab[i][j] == '>')
			{
				if (tab[i][j + 1] == '<' || tab[i][j + 1] == '>')
				{
					if (tab[i][j + 2] != '\0')
						return (1);
				}
				else if (tab[i][j + 1] != '\0')
					return (1);
			}
		}
	}
	return (ft_error_red2(tab));
}

int	env_size(t_shell *shell)
{
	t_varble	*temp;
	int			count;

	count = 0;
	temp = shell->variable;
	while (temp)
	{
		if (temp->in_env == 1)
			count++;
		temp = temp->next;
	}
	return (count);
}

char	**new_env(t_shell *shell)
{
	char		**env;
	int			i;
	t_varble	*temp;

	i = 0;
	temp = shell->variable;
	env = malloc(sizeof(char *) * (env_size(shell) + 1));
	while (temp)
	{
		if (temp->in_env == 1)
		{
			env[i] = ft_strdup(temp->entire_var);
			i++;
		}
		temp = temp->next;
	}
	return (env);
}

void	ft_heredoc(t_pipe *redir, t_exec *exec, t_shell *shell)
{
	char	*state_tab;
	char	**state_tmp;

	(void)shell;
	state_tmp = malloc(sizeof(char *) * 3);
	state_tab = redir->redir_dest[0];
	exec->fd[1] = STDOUT_FILENO;
	exec->fd_entry = exec->fd[0];
	state_tmp[0] = ft_strdup("cat");
	state_tmp[1] = ft_strdup("/tmp/heredoc");
	state_tmp[2] = NULL;
	exec->out_gestion = 3;
	gestion_heredoc(state_tab);
	if (ft_strcmp(shell->split_ipt[0], "cat") == 1)
		exec_cmd2(state_tmp, STDIN_FILENO, exec->fd[1], shell);
	return ;
}
