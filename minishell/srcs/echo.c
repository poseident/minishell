/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:07:01 by cdescour          #+#    #+#             */
/*   Updated: 2022/12/02 15:35:54 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_flag_n(char *str)
{
	int i;

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

void ft_convert(char *s, t_shell *shell)
{
	int double_quote;
	int simple_quote;
	int i;
	
	double_quote = 1;
	simple_quote = 1;
	i = 0;
	
	while(s[i])
	{
		if (s[i] == '"' && simple_quote == 1)
			double_quote = -double_quote + i++ * 0;
		else if (s[i] == '\'' && double_quote == 1)
			simple_quote = -simple_quote + i++ * 0;
		else if (simple_quote == 1 && s[i] == '$' && (s[i + 1] == '$' || s[i + 1] == '?'))
		{
			ft_print_variable(&s[i++], shell);
			i++;
		}
		else if (simple_quote == 1 && s[i] == '$' && (ft_isalnumz(s[i + 1])))
		{
			ft_print_variable(&s[i], shell);				
			while (ft_isalnum(s[++i]))
				;
		}
		else
			printf("%c", s[i++]);
	}
}

int ft_print_variable_2(char *tmp, t_shell *shell)
{
	struct s_varble *tmp2;
	tmp2 = shell->variable;
	while (tmp2)
	{
		if (ft_strchr(tmp , tmp2->var_name) == 1)
		{
			printf("%s", tmp2->var_data);
			return (1);
		}
		else
			tmp2 = tmp2->next;
	}
	return (1);
}

int ft_print_variable(char *s, t_shell *shell)
{
	int i;
	char *tmp;
	
	i = 1;
	if (s[i] == '$' || s[i] == '?')
	{
		if (s[i] == '$')
			printf("%d", getpid());
		else
			printf("[cas a traiter]");
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

void ft_echo(char **input, t_shell *shell)
{
	int i;
	int new_ligne;
	i = 0;
	new_ligne = 1;
	if (ft_flag_n(input[1]) == 1)
		new_ligne = ++i;
	while (input[++i])
	{
		ft_convert(input[i], shell);
		if (input[i + 1])
			printf(" ");
	}
	if (new_ligne != 2)
		printf("\n");
}
