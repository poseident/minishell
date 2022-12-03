#include "../include/minishell.h"

char *ft_fill_tmp_env(char *s)
{
	int i;
	char *tmp;

	i = 0;
	while (s[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '=')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int ft_g_envv_size(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->arg->g_envv[i])
		i++;
	return (i);
}

char **ft_g_envv_variable_name(t_shell *shell)
{
	int i;
	char **tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (shell->arg->g_envv_size + 1));
	while (shell->arg->g_envv[i])
	{
		tmp[i] = ft_fill_tmp_env(shell->arg->g_envv[i]);
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

int	ft_input_size(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->split_input[i])
		i++;
	return (i);
}

int envv_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void init_arg(t_shell *shell, char **envv)
{
	int i;
	int j;

	shell->arg = malloc(sizeof(t_arg) * 1);
	i = 0;
	while (envv[i])
		i++;
	shell->arg->g_envv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envv[i])
	{
		j = 0;
		shell->arg->g_envv[i] = malloc(sizeof(char) * (envv_len(envv[i]) + 1));
		while (envv[i][j])
		{
			shell->arg->g_envv[i][j] = envv[i][j];
			j++;
		}
		shell->arg->g_envv[i][j] = '\0';
		i++;
	}
	shell->arg->g_envv[i] = NULL;
	shell->arg->g_argv = ft_argv();
	shell->arg->g_envv_size = ft_g_envv_size(shell);
	shell->arg->g_env_var = ft_g_envv_variable_name(shell);
}

char **ft_argv(void)
{
	char **argv;

	argv = malloc(sizeof(char *) * 2);
	argv[0] = malloc(sizeof(char) * 12);
	argv[0] = "./minishell";
	argv[1] = NULL;
	return (argv);
}