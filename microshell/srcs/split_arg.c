/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:11:44 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/12 00:24:29 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_wordlen(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0' && (quote || \
		(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')))
	{
		check_quote(str[i], &quote);
		++i;
	}
	return (i);
}

char	*word_dupe(char *str)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = ft_wordlen(str);
	word = malloc(sizeof(char) * (len + 1));
	word[len] = '\0';
	while (i < len)
	{
		word[i] = str[i];
		++i;
	}
	return (word);
}

void	fill_words(char **array, char *str)
{
	int	word_index;
	int	quote;

	quote = 0;
	word_index = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		++str;
	while (*str != '\0')
	{
		array[word_index] = word_dupe(str);
		++word_index;
		while (*str && (quote || (*str != ' ' && *str != '\t' && *str != '\n')))
		{
			check_quote(*str, &quote);
			++str;
		}
		while (*str && !quote && (*str == ' ' || *str == '\t' || *str == '\n'))
		{
			check_quote(*str, &quote);
			++str;
		}
	}
}

int	count_words(char *str)
{
	int	num_words;
	int	quote;

	quote = 0;
	num_words = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		++str;
	while (*str != '\0')
	{
		++num_words;
		while (*str && (quote || (*str != ' ' && *str != '\t' && *str != '\n')))
		{
			check_quote(*str, &quote);
			++str;
		}
		while (*str && !quote && (*str == ' ' || *str == '\t' || *str == '\n'))
		{
			check_quote(*str, &quote);
			++str;
		}
	}
	return (num_words);
}

char	**ft_split_arg(char *str)
{
	char	**array;

	array = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (array)
		fill_words(array, str);
	return (array);
}
