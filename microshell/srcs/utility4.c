/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:25:56 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:22:51 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmd_after_pipe_error(char **input)
{
	int	i;

	i = 0;
	while (input[i++])
	{
		if (ft_strcmp(input[i], "|") == 1)
		{
			if (ft_builtin_checker2(input[i + 1]) == -1)
				return (-1);
		}
	}
	return (1);
}

char	*del_one_path(t_shell *shell)
{
	char	*tmp;
	int		i;
	char	*new;
	int		j;

	j = 0;
	i = 0;
	tmp = ft_strdup(get_pwd(shell));
	while (tmp[i] != '\0')
		i++;
	while (tmp[i] != '/')
		i--;
	new = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		new[j] = tmp[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_strjoin(char *str, char *temp)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new = malloc(sizeof(char) * ((ft_strlen(temp) + (ft_strlen(str)) + 1)));
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	while (temp[j])
	{
		new[i] = temp[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (cmp_char(s1[i], s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (cmp_char(s1[i], s2[i]));
	return (0);
}

int	cmp_char(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}
