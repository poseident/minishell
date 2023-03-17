/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:09:36 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:21:25 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**fill_dest(char **input, int redir)
{
	int		i;
	char	**dest;
	int		j;

	j = 0;
	i = redir + 1;
	dest = malloc(sizeof(char *) * (get_dest_len(input, redir) + 1));
	while (input[i] && (redir_array_or_not(input[i]) != 1))
	{
		dest[j] = ft_strdup(input[i]);
		j++;
		i++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**fill_source(char **input, int redir)
{
	char	**source;
	int		j;
	int		i;

	i = redir - 1;
	j = 0;
	source = malloc(sizeof(char *) * (get_source_len(input, redir) + 1));
	while ((redir_array_or_not(input[i]) != 1) && i > 0)
	{
		source[j] = ft_strdup(input[i]);
		j++;
		i--;
	}
	source[j] = NULL;
	return (source);
}

void	init_struct_next(t_shell *shell, int redir)
{
	int		new_redir_index;
	t_pipe	*temp;
	t_pipe	*newnode;

	new_redir_index = redir_index(shell->split_ipt, redir + 1);
	newnode = (t_pipe *)malloc(sizeof(t_pipe));
	temp = shell->str_pipe;
	while (temp->next)
		temp = temp->next;
	newnode->redir = ft_strdup(shell->split_ipt[new_redir_index]);
	newnode->redir_dest = fill_dest(shell->split_ipt, new_redir_index);
	newnode->redir_source = fill_source(shell->split_ipt, new_redir_index);
	newnode->next = NULL;
	temp->next = newnode;
}

void	ft_init_struct(t_shell *shell)
{
	int	redir;

	shell->str_pipe = malloc(sizeof(t_pipe));
	redir = redir_index(shell->split_ipt, 0);
	shell->str_pipe->redir_source = source_redir(shell->split_ipt, redir);
	shell->first_cmd = source_redir(shell->split_ipt, redir);
	shell->str_pipe->redir = ft_strdup(shell->split_ipt[redir]);
	shell->str_pipe->redir_dest = fill_dest(shell->split_ipt, redir);
	shell->str_pipe->next = NULL;
	while (shell->sep_count-- > 1)
	{
		init_struct_next(shell, redir);
		redir = redir_index(shell->split_ipt, redir + 1);
	}
	exec_redirection(shell);
}

int	redir_array_or_not(char *str)
{
	if (ft_strcmp(str, ">") == 1)
		return (1);
	if (ft_strcmp(str, ">>") == 1)
		return (1);
	if (ft_strcmp(str, "<") == 1)
		return (1);
	if (ft_strcmp(str, "<<") == 1)
		return (1);
	return (-1);
}
