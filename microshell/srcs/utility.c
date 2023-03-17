/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:04:38 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:24:21 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_redir(char **split_input)
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
				if (split_input[i][j] == '<' || split_input[i][j] == '>')
					return (1);
			}
		}
	}
	return (0);
}

int	ft_strchr(char *input, char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (input[i] && s[i])
	{
		if (input[i] != s[i])
			return (-1);
		i++;
	}
	if (input[i] == '\0' && s[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_flag_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 2)
	{
		if (str[0] == '-' && str[1] == 'n')
			return (1);
	}
	return (-1);
}

int	ft_isalnumz(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '$' || c == '?')
		return (1);
	return (0);
}

char	*ft_variable_name_without_dollar(char *s)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(s)));
	i++;
	while (s[i])
	{
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
