/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:00:15 by cdescour          #+#    #+#             */
/*   Updated: 2022/12/02 16:33:19 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int input_size(char *input)
{
    int i;
    int j;
    int len;
    int count;

    count = 0;
    i = 0;
    j = 0;
    while (input[i] && input[i] <= 32)
        i++;
    while (input[j])
        j++;
    j--;
    while (input[j] <= 32)
    {
        count++;
        j--;
    }
    count += i;
    len = (ft_strlen(input) - count);
    return (len);
}

int ft_last_caractere(char *input)
{
    int i;

    i = 0;
    while (input[i])
        i++;
    i--;
    while (input[i] <= 32)
        i--;
    return (i);
}

char *first_clear(char *input)
{
    char *tmp;
    int i;
    int j;

    j = 0;
    i = 0;
    tmp = malloc(sizeof(char) * (input_size(input) + 1));
    while (input[i] <= 32 && input[i])
        i++;
    while (input[i] && i <= ft_last_caractere(input))
    {
        tmp[j] = input[i];
        j++;
        i++;
    }
    tmp[j] = '\0';
    return (tmp);
}

int tmp_cleaned(char *tmp)
{
    int i;
    int quote;
    int count;

    i = 0;
    count = 0;
    while (tmp[i])
    {
        quote = 0;
		if (tmp[i] <= 32 && quote == 0 && tmp[i + 1] <= 32)
			count++;
		else if (tmp[i] == 34)
		{
			quote = 1;
			while (quote != 2 && tmp[i])
			{
				i++;
				if (tmp[i] == 34)
					quote = 2;
			}
			if (quote == 1)
				return (-1);
		}
		else if (tmp[i] == 39)
		{
			quote = 1;
			while (quote != 2 && tmp[i])
			{
				i++;
				if (tmp[i] == 39)
					quote = 2;
			}
			if (quote == 1)
				return (-1);
		}
		i++;
    }
    return (count);
}

char *ft_input_shell(char *input)
{
    char *tmp;
    int i;
    char *cleaned;
    int quote;
    int j;

    j = 0;
    i = 0;
    tmp = first_clear(input);
    cleaned = malloc(sizeof(char) * (ft_strlen(tmp) - (tmp_cleaned(tmp)) + 1));
    while (tmp[i])
    {
        quote = 0;
        if (tmp[i] <= 32 && tmp[i + 1] <= 32 && quote == 0)
            i++;
        else
        {
            cleaned[j] = tmp[i];
            j++;
            i++;
        }
    }
    cleaned[j] = '\0';
    return (cleaned);
}

void ft_parsing(t_shell *shell)
{
    int i;
    i = 0;
    shell->split_input = ft_split_input(shell->input);
	return ;
}