/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:08:11 by bschweit          #+#    #+#             */
/*   Updated: 2022/12/02 16:30:55 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//rl_clear_history (void) clear history;

int ft_minishell(char *input, t_shell *shell)
{
	shell->index = 0;
	if (ft_checker(input) == -1)
		return (0);
	ft_parsing(shell);
	shell->input_size = ft_input_size(shell);
	if (ft_builtin_checker(shell) == -1)
	{
		printf("faux\n");
		//ft_free(shell);
		return (0);
	}
	else
		ft_exec_command(shell);
	return (0);
}

int	main(int argc, char **argv, char **envv)
{
	t_shell *shell;
	int loop;

	(void)argv;
	(void)argc;
	loop = 0;
	shell = malloc(sizeof(t_shell) * 1);
	shell->variable = ((struct s_varble *)malloc(sizeof(struct s_varble)));
	shell->count = 0;
	shell->var_idx = 0;
	init_arg(shell, envv);
	while (!loop)
	{
		shell->input = readline(print_prompt());
		if (shell->input)
        	add_history(shell->input);
		loop = ft_minishell(shell->input, shell);
	}
}