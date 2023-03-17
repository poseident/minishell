/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:00:15 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/20 00:06:46 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

char	*ft_putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split_words(char *s, char **s2, int n, char *s3)
{
	int		i;
	int		word;
	int		word_len;
	char	c;

	i = 0;
	word = -1;
	word_len = 0;
	c = ' ';
	while (++word < n)
	{
		while (s3[i] && s3[i] == c)
			i++;
		while (s3[i] && s3[i] != c)
		{
			i++;
			word_len++;
		}
		s2[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		ft_putword(s2[word], s, i, word_len);
		word_len = 0;
	}
	s2[word] = 0;
	return (s2);
}

char	*ft_cp(char *s)
{
	int		i;
	int		len;
	char	*sc;

	len = 0;
	while (s[len])
		len++;
	sc = malloc(sizeof(char) * (len + 1));
	if (!sc)
		return (0);
	i = 0;
	while (s[i])
	{
		sc[i] = s[i];
		i++;
	}
	sc[i] = '\0';
	return (&sc[0]);
}

char	**ft_split_input(char *s, t_shell *shell)
{
	char			**s2;
	unsigned int	num_words;
	char			*strcpy;
	char			c;

	c = ' ';
	strcpy = ft_cp(s);
	ft_lexer_simplify_count(strcpy);
	ft_lexer_simplify_count2(strcpy);
	if (!s)
		return (0);
	num_words = ft_count_words(strcpy, c);
	shell->split_input_size = num_words;
	s2 = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!s2)
		return (0);
	ft_split_words(s, s2, num_words, strcpy);
	free(strcpy);
	return (s2);
}
