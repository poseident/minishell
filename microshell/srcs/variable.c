/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:02:56 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/20 01:19:15 by cdescour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_clean_variable(t_shell *shell)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (shell->split_input_size + 1));
	while (shell->split_ipt[i])
	{
		tmp[i] = ft_fill_cleaned_variable(shell->split_ipt[i]);
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	*ft_fill_variable_name(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] != '=' && s[i])
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '=' && s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_fill_variable_data(char *s)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	i = 0;
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

void	ft_fill_variable(t_shell *s)
{
	int				i;
	t_varble		*temp;
	struct s_varble	*newnode;

	i = -1;
	temp = s->variable;
	while (temp->next != NULL)
		temp = temp->next;
	if (s->cleaned_variable[0] != 0)
	{
		while (s->cleaned_variable[++i])
		{
			newnode = (struct s_varble *)malloc(sizeof(struct s_varble));
			newnode->var_data = ft_fill_variable_data(s->cleaned_variable[i]);
			newnode->var_name = ft_fill_variable_name(s->cleaned_variable[i]);
			newnode->entire_var = ft_strdup(s->cleaned_variable[i]);
			newnode->deleted = 0;
			newnode->in_env = 0;
			newnode->next = NULL;
			temp->next = newnode;
			temp = temp->next;
		}
	}
	return ;
}
