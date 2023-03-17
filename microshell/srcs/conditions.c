/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:35:11 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/20 01:24:07 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_quote(char c, int *quotes)
{
	if (c == '\'' && *quotes == 1)
		*quotes = 0;
	else if (c == '"' && *quotes == 2)
		*quotes = 0;
	else if (c == '\'' && *quotes == 0)
		*quotes = 1;
	else if (c == '"' && quotes == 0)
		*quotes = 2;
}

int	check_condition(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2))
		return (2);
	return (0);
}

int	check_pipe(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}

int	check_redirection(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}
