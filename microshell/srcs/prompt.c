/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:22:31 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/19 23:26:42 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*to_prompt(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*x;

	j = 0;
	i = 0;
	x = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 4));
	while (s1[i])
	{
		x[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		x[i] = s2[j];
		j++;
		i++;
	}
	x[i] = '$';
	x[++i] = '>';
	x[++i] = ' ';
	x[++i] = '\0';
	return (x);
}

char	*print_prompt(void)
{
	char	*user;
	char	*directory;
	char	*x;

	user = ft_user();
	directory = ft_pwd();
	x = to_prompt(user, directory);
	return (x);
}

char	*ft_pwd(void)
{
	char	*d;
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	d = malloc(sizeof(char) * (ft_strlen(getenv("PWD"))));
	d = getenv("PWD");
	if (d == NULL)
		d = "";
	while (d[i])
		i++;
	while (d[i] != '/')
		i--;
	s = malloc(sizeof(char) * (ft_strlen(d) - i + 1));
	while (d[i])
	{
		s[j] = d[i];
		j++;
		i++;
	}
	s[j] = '\0';
	return (s);
}

char	*ft_user(void)
{
	char	*user;

	if (getenv("USER"))
	{
		user = malloc(sizeof(char) * (ft_strlen(getenv("USER")) + 1));
		user = getenv("USER");
		user[ft_strlen(getenv("USER"))] = '\0';
	}
	else if (getenv("USERNAME"))
	{
		user = malloc(sizeof(char) * ft_strlen(getenv("USERNAME")));
		user = getenv("USERNAME");
		if (user == NULL)
			user = "";
	}
	else
	{
		user = malloc(sizeof(char) * 7);
		user = "NoUSER";
	}
	return (user);
}
