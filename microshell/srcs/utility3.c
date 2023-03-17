/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:15:06 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:23:02 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	sep_or_not(char *str)
{
	if (ft_strcmp(str, "|") == 1)
		return (1);
	if (ft_strcmp(str, ">") == 1)
		return (1);
	if (ft_strcmp(str, ">>") == 1)
		return (1);
	if (ft_strcmp(str, "<<") == 1)
		return (1);
	if (ft_strcmp(str, "<") == 1)
		return (1);
	return (-1);
}

int	ft_strcmp(char *str, char *cmp)
{
	int	i;

	i = 0;
	if (!str || !cmp)
		return (-1);
	while (str[i] == cmp[i] && str[i] != '\0' && cmp[i] != '\0')
		i++;
	if (str[i] == '\0' && cmp[i] == '\0')
		return (1);
	else
		return (-1);
}

int	ft_sep_count(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (redir_array_or_not(input[i]) == 1)
			count++;
		i++;
	}
	return (count);
}

char	*ft_get_var_data(char *s)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (ft_strlen(s) - i));
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

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
