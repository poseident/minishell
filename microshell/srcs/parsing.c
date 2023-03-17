/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:00:15 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/20 01:28:46 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	*first_clear(char *input)
{
	char	*tmp;
	int		i;
	int		j;

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

int	tmp_c(char *tmp, int count, int i)
{
	int	quote;

	i = -1;
	count = 0;
	while (tmp[++i])
	{
		quote = 0;
		if (tmp[i] <= 32 && quote == 0 && tmp[i + 1] <= 32)
			count++;
		else if (tmp[i] == 34)
		{
			quote = 1;
			while (quote != 2 && tmp[i])
			{
				if (tmp[++i] == 34)
					quote = 2;
			}
			if (quote == 1)
				return (-1);
		}
		else if (tmp[i] == 39)
			if (tmp_cleaned2(tmp, &i) == -1)
				return (-1);
	}
	return (count);
}

int	tmp_cleaned2(char *tmp, int *i)
{
	int	quote;

	quote = 1;
	while (quote != 2 && tmp[*i])
	{
		if (tmp[++*i] == 39)
		quote = 2;
	}
	if (quote == 1)
		return (-1);
	return (0);
}

char	*ft_input_shell(char *input)
{
	char	*tmp;
	int		i;
	char	*cleaned;
	int		quote;
	int		j;

	j = 0;
	i = 0;
	tmp = first_clear(input);
	cleaned = malloc(sizeof(char) * (ft_strlen(tmp) - (tmp_c(tmp, 0, 0)) + 1));
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

void	ft_parsing(t_shell *shell)
{
	shell->split_ipt = ft_split_input(shell->input, shell);
	shell->split_input_size = ft_input_size(shell);
	shell->sep_count = ft_sep_count(shell->split_ipt);
	shell->bin = fill_bin();
	return ;
}
