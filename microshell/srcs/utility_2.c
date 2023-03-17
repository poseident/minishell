/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:11:52 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:23:16 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_shell_len(char **envv)
{
	int	i;

	i = 0;
	while (envv[i])
		i++;
	return (i + 1);
}

char	**ft_copy_env(char **envv)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * ft_shell_len(envv) + 1);
	while (envv[i])
	{
		new[i] = ft_strdup(envv[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

char	*ft_strdup(char *tmp)
{
	int		i;
	char	*line;

	i = 0;
	if (!tmp)
		return (NULL);
	line = malloc(sizeof(char) * ft_strlen(tmp) + 1);
	while (tmp[i])
	{
		line[i] = tmp[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
