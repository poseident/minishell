/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:10:15 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:22:27 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_index(char **input, int start)
{
	int	i;

	i = start;
	while (input[i])
	{
		if (redir_array_or_not(input[i]) == 1)
			return (i);
		i++;
	}
	return (-1);
}

int	sep_error(char **t)
{
	int	i;

	i = 0;
	while (t[i++])
	{
		if ((ft_strcmp(t[i], "|") == 1) && (ft_strcmp(t[i + 1], "|") == 1))
			return (-1);
		if ((ft_strcmp(t[i], ">") == 1) && (ft_strcmp(t[i + 1], ">") == 1))
			return (-1);
		if ((ft_strcmp(t[i], ">>") == 1) && (ft_strcmp(t[i + 1], ">>") == 1))
			return (-1);
		if ((ft_strcmp(t[i], "<<") == 1) && (ft_strcmp(t[i + 1], "<<") == 1))
			return (-1);
		if ((ft_strcmp(t[i], "<") == 1) && (ft_strcmp(t[i + 1], "<") == 1))
			return (-1);
	}
	return (1);
}

int	redir_not2(char c)
{
	if (c == '>')
		return (1);
	return (0);
}

int	redir_not(char c)
{
	if (c == '<')
		return (1);
	return (0);
}

int	ft_redir_check2(char **t)
{
	int	i;
	int	j;

	i = 0;
	while (t[i])
	{
		j = 0;
		while (t[i][j])
		{
			if ((redir_not(t[i][j]) == 1) && (redir_not2(t[i][j + 1]) == 1))
				return (-1);
			if ((redir_not(t[i][j + 1]) == 1) && (redir_not2(t[i][j]) == 1))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
