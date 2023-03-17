/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:07:01 by cdescour          #+#    #+#             */
/*   Updated: 2023/01/20 01:18:38 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_convert(char *s, t_shell *shell, int i)
{
	t_tmp	tmp;

	tmp.double_quote = 1;
	tmp.sq = 1;
	while (s[i])
	{
		if (s[i] == '"' && tmp.sq == 1)
			tmp.double_quote = -tmp.double_quote + 0 * i++;
		else if (s[i] == '\'' && tmp.double_quote == 1)
			tmp.sq = -tmp.sq + 0 * i++;
		else if (tmp.sq == 1 && s[i] == '$'
			&& (s[i + 1] == '$' || s[i + 1] == '?'))
		{
			ft_print_variable(&s[i++], shell);
			i++;
		}
		else if (tmp.sq == 1 && s[i] == '$' && (ft_isalnumz(s[i + 1])))
		{
			ft_print_variable(&s[i], shell);
			while (ft_isalnum(s[++i]))
				;
		}
		else
			printf("%c", s[i++]);
	}
}

int	ft_print_variable_2(char *tmp, t_shell *shell)
{
	t_varble	*tmp2;

	tmp2 = shell->variable;
	while (tmp2)
	{
		if (ft_strchr(tmp, tmp2->var_name) == 1)
		{
			if (tmp2->deleted == 0)
				printf("%s", tmp2->var_data);
			return (1);
		}
		else
			tmp2 = tmp2->next;
	}
	return (1);
}

int	ft_print_variable(char *s, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 1;
	if (s[i] == '$' || s[i] == '?')
	{
		if (s[i] == '$')
			printf("24659");
		else if (s[i] == '?')
			printf("%d", shell->sucess_cmd);
		return (1);
	}
	while (ft_isalnum(s[i]) == 1)
		i++;
	tmp = malloc(sizeof(char) * i);
	i = 0;
	while (ft_isalnum(s[++i]) == 1)
		tmp[i - 1] = s[i];
	tmp[i - 1] = '\0';
	ft_print_variable_2(tmp, shell);
	free (tmp);
	return (1);
}

void	ft_echo(char **input, t_shell *shell)
{
	int	i;
	int	new_ligne;

	i = 0;
	new_ligne = 1;
	if (!input[1])
	{
		printf("\n");
		return ;
	}
	if (ft_flag_n(input[1]) == 1)
	{
		new_ligne = 2;
		++i;
	}
	while (input[++i])
	{
		ft_convert(input[i], shell, 0);
		if (input[i + 1])
			printf(" ");
	}
	if (new_ligne != 2)
		printf("\n");
	return ;
}
