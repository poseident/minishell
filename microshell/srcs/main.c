/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:08:11 by bschweit          #+#    #+#             */
/*   Updated: 2023/01/19 22:51:45 by bschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_init_sigal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int	ft_minishell(char *input, t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_checker(input) == -1)
		return (0);
	ft_parsing(shell);
	if ((shell->split_ipt[0]))
	{
		if (ft_error_red(shell->split_ipt))
		{
			printf("zsh: parse error near `\\n'\n");
			return (0);
		}
		ft_exec_command(shell);
	}
	return (0);
}

int	main(int argc, char **argv, char **envv)
{
	t_shell	*shell;
	int		loop;

	(void)argv;
	(void)argc;
	loop = 0;
	shell = malloc(sizeof(t_shell) * 1);
	shell->sucess_cmd = 0;
	shell->env = ft_copy_env(envv);
	ft_init_chain(shell, envv);
	ft_init_sigal();
	while (!loop)
	{
		shell->input = readline((print_prompt()));
		if (shell->input == NULL)
			exit(0);
		if (shell->input)
		{
			add_history(shell->input);
		}
		loop = ft_minishell(shell->input, shell);
	}
}
