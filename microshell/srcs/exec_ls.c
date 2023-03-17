/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:13:48 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:18:29 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_get_path(t_shell *shell)
{
	int	i;
	int	j;
	int	y;

	i = 1;
	shell->input_ls = malloc(sizeof(char *) * (shell->split_input_size + 1));
	shell->input_ls[0] = malloc(sizeof(char) * 12);
	shell->input_ls[0] = "./minishell";
	while (shell->split_ipt[i] != NULL)
	{
		y = ft_strlen(shell->split_ipt[i]);
		j = 0;
		shell->input_ls[i] = malloc(sizeof(char) * (y + 1));
		while (shell->split_ipt[i][j])
		{
			shell->input_ls[i][j] = shell->split_ipt[i][j];
			j++;
		}
		shell->input_ls[i][j] = '\0';
		i++;
	}
	shell->input_ls[i] = 0;
}
