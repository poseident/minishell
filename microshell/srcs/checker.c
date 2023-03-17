/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:24:49 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:25:13 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_checker(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (-1);
	else if (nothing_check(input) == -1)
		return (-1);
	else if (quote_check(input) == -1)
	{
		printf("quote>\n");
		return (-1);
	}
	else
		return (0);
}

int	ft_into_next(char *input, int *i, char c)
{
	while (input[++*i])
	{
		if (input[*i] == c)
			return (1);
	}
	return (-1);
}

int	quote_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 39)
		{
			if (ft_into_next(input, &i, input[i]) == -1)
				return (-1);
		}
		else if (input[i] == 34)
		{
			if (ft_into_next(input, &i, input[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	nothing_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] <= 32)
		i++;
	if (input[i] == '\0')
		return (-1);
	else
		return (0);
}

int	no_pipe(char **split_input)
{
	int	i;
	int	j;

	i = -1;
	while (split_input[++i])
	{
		j = -1;
		while (split_input[i][++j] != '\0')
		{
			if (split_input[i][j] == 34 || split_input[i][j] == 39)
				break ;
			else
			{
				if (split_input[i][j] == '|')
					return (1);
			}
		}
	}
	return (0);
}
