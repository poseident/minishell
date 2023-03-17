/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:23:59 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:24:48 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env(t_shell *shell)
{
	t_varble	*tmp;

	tmp = shell->variable;
	while (tmp)
	{
		if (tmp->in_env == 1)
			printf("%s\n", tmp->entire_var);
		tmp = tmp->next;
	}
	shell->sucess_cmd = 0;
}

char	*ft_print_pwd(t_shell *shell)
{
	t_varble	*tmp;
	char		*pwd;
	int			i;

	i = 0;
	tmp = shell->variable;
	while (ft_strchr(tmp->var_name, "PWD") != 1)
		tmp = tmp->next;
	pwd = malloc(sizeof(char) * ft_strlen(tmp->var_data) + 1);
	while (tmp->var_data[i])
	{
		pwd[i] = tmp->var_data[i];
		i++;
	}
	pwd[i] = '\0';
	return (pwd);
}
