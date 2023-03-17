/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:19:47 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:21:42 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_fill_cleaned_variable(char *input)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = malloc(sizeof(char) * (ft_variable_len(input) + 1));
	ft_sub_3(&i, &j, tmp, input);
	while (input[i])
	{
		if (input[i] == 34)
			ft_sub_1(&i, &j, tmp, input);
		else if (input[i] == 39)
			ft_sub_2(&i, &j, tmp, input);
		else
		{
			tmp[j] = input[i];
			j++;
			i++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_sub_1(int *i, int *j, char *tmp, char *input)
{
	(*i)++;
	while (input[*i] != 34 && input[*i])
	{
		tmp[*j] = input[*i];
		(*j)++;
		(*i)++;
	}
	if (input[*i] == 34)
		(*i)++;
	return ;
}

void	ft_sub_2(int *i, int *j, char *tmp, char *input)
{
	(*i)++;
	while (input[*i] != 39 && input[*i])
	{
		tmp[*j] = input[*i];
		(*j)++;
		(*i)++;
	}
	if (input[*i] == 39)
		(*i)++;
	return ;
}

void	ft_sub_3(int *i, int *j, char *tmp, char *input)
{
	while (input[*i] != '=')
	{
		tmp[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
	tmp[*j] = '=';
	(*i)++;
	(*j)++;
	return ;
}
