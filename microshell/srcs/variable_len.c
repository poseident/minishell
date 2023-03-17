/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:31:31 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:20:22 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_variable_len_sub1(char *input, int *i, int *count)
{
	while (input[*i] != '=')
	{
		(*count)++;
		(*i)++;
	}
	(*count)++;
	(*i)++;
	return ;
}

void	ft_variable_len_sub2(char *input, int *i, int *count)
{
	(*i)++;
	while (input[*i] != 34 && input[*i])
	{
		(*i)++;
		(*count)++;
	}
	if (input[*i] == 34)
		(*i)++;
	return ;
}

void	ft_variable_len_sub3(char *input, int *i, int *count)
{
	(*i)++;
	while (input[*i] != 39 && input[*i])
	{
		(*i)++;
		(*count)++;
	}
	if (input[*i] == 39)
		(*i)++;
	return ;
}

int	ft_variable_len(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	ft_variable_len_sub1(input, &i, &count);
	while (input[i])
	{
		if (input[i] == 34)
			ft_variable_len_sub2(input, &i, &count);
		else if (input[i] == 39)
			ft_variable_len_sub3(input, &i, &count);
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}
